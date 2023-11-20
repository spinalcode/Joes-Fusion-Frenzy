#pragma once

#include <new>
#include <File>

#define ALIGNED __attribute__ ((aligned))
#define NAKED __attribute__((naked))

namespace Audio {

    class ADPCMSource {
        // WAVE file WavHeader format
        struct WavHeader {
            u8 riff[4];				// (1-4)  RIFF string
            u32 overall_size;       // (5-8)  overall size of file in bytes
            u8 wave[4];				// (9-12) WAVE string
            u8 fmt_chunk_marker[4]; // (13-16) fmt string with trailing null char
            u32 length_of_fmt;		// (17-20) length of the format data
            u16 format_type;		// (21-22) format type. 1-PCM, 3- IEEE float, 6 - 8bit A law, 7 - 8bit mu law
            u16 channels;			// (23-24) no.of channels
            u32 sample_rate;		// (25-28) sampling rate (blocks per second)
            u32 byterate;			// (29-32) SampleRate * NumChannels * BitsPerSample/8
            u16 block_align;		// (33-34) NumChannels * BitsPerSample/8
            u16 bits_per_sample;    // (35-36) bits per sample, 8- 8bits, 16- 16 bits etc
        	
            // If format != PCM then there is extra data here
            // format 17 is ima adpcm
            struct ExtraData {
            	u16 extraDataSize;	//  2 for IAM ADPCM
            	u16 data_size;		//  Samples per block (IMA ADPCM)
            	u8 subID[4];        //	"fact"
                u32 subSize;		//  size of next data
            } extraData;
                
            struct DATA_WavHeader {
            	u8 data_chunk_WavHeader [4];    // DATA string or FLLR string
                u32 data_size;		// filesize - 60
            } dataWavHeader;
        };
        
        int predictor = 0;
        int index = 0;
        int blockAlign;
        
        File *file;
        u32 start;
        u32 fileOffset;
        u32 blockOffset;
        u32 length;
        bool paused;
        bool loop;

        static void copy(u8 *buffer, void *ptr){
            auto &sd = *reinterpret_cast<ADPCMSource*>(ptr);
            auto &file = *sd.file;
            u32 fileOffset = file.tell();
            if(sd.paused || (fileOffset - sd.start) >= sd.length){
                MemOps::set(buffer, 127, 512);
                return;
            }
            int predictor = sd.predictor;
            for (u32 outOffset = 0; outOffset < 512;) {
                if (fileOffset >= sd.length) {
                    if (sd.loop) {
                        file.seek(sd.fileOffset);
                        fileOffset = sd.fileOffset;
                        while (outOffset < 512) {
                            buffer[outOffset++] = 127;
                        }
                        sd.blockOffset=0; // reset this or it no longer decodes correctly.
                        break;
                    }
                }
                
                if (sd.blockOffset == 0) {
                    sd.blockOffset = sd.blockAlign - 4;
                    predictor = file.read<s16>();
                    sd.index  = file.read<u8>();
                    file.read<u8>(); // unused junk byte
                    fileOffset += 4;
                }
                s32 max = (sd.blockOffset * 2 > (512 - outOffset) ? (512 - outOffset) : sd.blockOffset * 2) >> 1;
                sd.blockOffset -= max;
                fileOffset += max;
                while (max--) {
                    u32 pair = file.read<u8>();
                    predictor = sd.decode(pair & 15, predictor);
                    buffer[outOffset++] = (predictor + 0x8080) >> 8;
                    predictor = sd.decode(pair >> 4, predictor);
                    buffer[outOffset++] = (predictor + 0x8080) >> 8;
                }
            }
            sd.predictor = predictor;
        }

        static void mix(u8 *buffer, void *ptr){
            u8 tmpbuf[512];
            copy(tmpbuf, ptr);
            Audio::mix(buffer, tmpbuf, 512);
        }
        
        void init(File& wavFile) {
            file = &wavFile;
            WavHeader header;
            readADPCMWavHeader(wavFile, header);
            start = wavFile.tell();
            length = header.overall_size;
            fileOffset = start;
            loop = false;
            blockAlign = header.block_align;
            blockOffset = 0;
        }

        int decode(int nibble, int predictor) {
            s32 step = stepTable[index];
            index += indexTable[nibble];
            if (index < 0){
                index = 0;
            } else if (index > 88){
                index = 88;
            }

            int sign = nibble & 8;
            int delta = nibble & 7;
            int diff = ((2 * delta + 1) * step) >> 3;
            if (sign) predictor -= diff;
            else predictor += diff;

            if (predictor < -0x8000){
                predictor = -0x8000;
            } else if (predictor > 0x7fff){
                predictor = 0x7fff;
            }

            return predictor;
        }

        void readADPCMWavHeader(File& file, WavHeader& header){
            file.read(&header, 60);
        }

        static inline constexpr const s8 indexTable[16] = {
            -1, -1, -1, -1, 2, 4, 6, 8,
            -1, -1, -1, -1, 2, 4, 6, 8,
        };

        static inline constexpr const u16 stepTable[89] = {
            7, 8, 9, 10, 11, 12, 13, 14, 16, 17, 19, 21, 23, 25, 28, 31, 34,
            37, 41, 45, 50, 55, 60, 66, 73, 80, 88, 97, 107, 118, 130, 143,
            157, 173, 190, 209, 230, 253, 279, 307, 337, 371, 408, 449, 494,
            544, 598, 658, 724, 796, 876, 963, 1060, 1166, 1282, 1411, 1552,
            1707, 1878, 2066, 2272, 2499, 2749, 3024, 3327, 3660, 4026,
            4428, 4871, 5358, 5894, 6484, 7132, 7845, 8630, 9493, 10442,
            11487, 12635, 13899, 15289, 16818, 18500, 20350, 22385, 24623,
            27086, 29794, 32767
        };

    public:
        template<u32 channel = 0>
        static ADPCMSource &getSourceInstance(){
            static ADPCMSource sd;
            return sd;
        }

        template<u32 channel = 0>
        static ADPCMSource &play(File& fileRef){
            auto& sd = getSourceInstance<channel>();
            sd.init(fileRef);
            Audio::connect(channel, &sd, channel == 0 ? copy : mix);
            return sd;
        }
        
        template<u32 channel = 0>
        static ADPCMSource *play(const char *name){
            static ALIGNED u8 ram[sizeof(File)];
            static bool init = false;
            if(!init){
                new (static_cast<void*>(ram)) File();
                init = true;
            }

            File& file = *reinterpret_cast<File*>(ram);
            if(file.openRO(name)){
                return &play<channel>(file);
            } else {
                Audio::stop<channel>();
            }
            return nullptr;
        }

        ADPCMSource& setPaused(bool isPaused){
            paused = isPaused;
            return *this;
        }
        
        ADPCMSource& setLoop(bool doesLoop){
            loop = doesLoop;
            return *this;
        }

        u32 getPosition(){
            return (fileOffset - start);
        }

        bool ended(){
            return (fileOffset - start) >= length;
        }
    };
}
