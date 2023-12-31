const uint16_t background_map[] = {
    28,22,
    1,1,2,3,4,5,6,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,8,8,9,10,11,12,13,14,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,15,8,16,8,17,18,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,19,20,21,8,8,8,8,8,8,8,8,8,8,8,19,22,21,8,8,8,23,24,21,8,8,8,8,8,25,26,27,28,1,2,3,4,5,6,7,1,1,29,30,31,32,8,8,8,33,34,35,36,8,8,8,8,8,37,38,8,8,9,10,11,12,13,14,8,8,8,8,39,40,8,8,8,41,42,43,44,8,8,8,8,8,45,46,8,8,15,8,16,8,17,18,8,8,8,8,47,8,8,8,8,48,49,50,51,52,53,54,55,56,57,58,59,8,8,8,8,8,8,8,8,8,59,60,61,53,52,53,56,62,63,52,64,65,66,67,68,69,70,71,72,8,8,8,8,8,8,8,8,8,72,73,74,66,65,66,69,66,65,66,69,75,76,77,78,75,79,8,8,8,8,8,8,8,8,8,8,8,8,8,80,76,75,76,75,76,75,76,75,76,75,81,82,76,83,8,8,8,8,8,8,8,8,8,8,8,8,8,84,75,76,75,76,75,76,75,76,75,76,77,85,75,79,8,8,8,8,8,8,8,8,8,8,8,8,8,80,76,75,76,75,76,75,76,75,76,75,86,87,76,83,8,8,8,8,8,8,8,8,8,8,8,8,8,84,75,76,75,76,75,76,75,76,75,76,75,76,75,79,8,8,8,8,8,8,8,8,8,8,8,8,8,80,76,75,76,75,76,75,76,75,76,75,76,75,76,83,8,8,8,8,8,8,8,8,8,8,8,8,8,84,75,76,75,76,75,76,75,76,75,76,75,76,75,79,8,8,8,8,8,8,8,8,8,8,8,8,8,80,76,75,76,75,76,75,76,75,76,75,76,75,76,83,8,8,8,8,8,8,8,8,8,8,8,8,8,84,75,76,75,76,75,76,75,76,75,76,75,76,75,79,8,8,8,8,8,8,8,8,8,8,8,8,8,80,76,75,76,75,76,75,76,75,76,75,76,75,76,83,8,8,8,8,8,8,8,8,8,8,8,8,8,88,75,76,75,76,75,76,75,76,75,76,75,89,90,91,52,53,52,92,56,93,94,95,94,95,96,97,98,99,76,75,76,75,76,75,76,75,76,75,76,100,101,66,65,66,102,103,69,104,105,104,105,104,106,67,68,107,75,76,75,76,75,76,75,76
};

const uint16_t background_Tiles_pal[] = {
    25791,0,54565,43809,512,1408,896,33184,48163,14336,37408,24800,8192,20640,18496,28992,1920,800,1120,8452,608,1024,65189,16359,65535,
};


const uint8_t background_Tiles[] =
{
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 2,2,2,2,2,2,2,2, 3,3,3,3,3,3,3,3, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 2,2,2,2,2,2,2,2, 3,3,3,3,3,3,3,3, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,1,1,1, 0,0,0,0,1,20,5,17, 1,1,1,1,20,5,18,4, 2,2,2,1,6,16,4,2, 3,3,3,1,6,22,1,3, 1,1,1,1,6,16,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 2,2,2,2,2,2,2,2, 3,3,3,3,3,3,3,3, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 0,0,0,0,0,0,1,5, 1,1,1,1,1,1,5,6, 2,2,2,2,1,16,6,4, 3,3,1,1,5,17,4,1, 4,20,5,5,17,4,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,0,0,0,0,0,0, 5,6,1,0,0,0,0,0, 4,1,1,1,1,1,1,1, 1,2,2,2,2,2,2,2, 3,3,3,3,3,3,3,3, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,1,0,1,1, 0,0,1,1,1,1,20,6, 1,1,1,1,1,1,1,1, 2,2,2,2,2,2,2,2, 3,3,3,3,3,3,3,3, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,0,0,0,0,0,0, 5,6,1,0,0,0,0,0, 4,5,6,1,1,1,1,1, 1,16,6,1,2,2,2,2, 1,5,6,1,3,3,3,3, 1,5,6,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,1,6,5,1,20, 0,0,0,1,17,5,1,6, 0,0,0,1,20,5,1,4, 0,0,0,1,4,5,1,1, 0,0,0,0,4,5,1,0, 0,0,0,0,1,5,1,0, 0,0,0,0,1,5,1,0, 0,0,0,0,1,5,1,0, 6,18,18,18,18,5,5,5, 4,1,1,4,4,4,4,4, 1,1,1,1,1,1,1,1, 0,1,1,0,0,0,0,0, 0,0,1,0,0,0,0,0, 0,0,1,0,0,0,0,0, 0,0,1,0,0,0,0,0, 0,0,0,0,0,0,0,0, 5,5,6,17,4,1,1,1, 4,4,1,1,1,1,1,1, 1,0,1,1,0,1,1,1, 0,0,1,0,0,0,1,1, 0,0,1,0,0,0,1,1, 0,0,1,0,0,0,1,0, 0,0,1,0,0,0,1,0, 0,0,1,0,0,0,1,0, 0,1,6,1,0,0,0,0, 0,1,5,1,0,0,0,0, 0,1,6,1,0,0,0,0, 0,0,1,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,1,1,0,1,1,1, 0,0,1,1,0,1,1,0, 0,0,1,1,0,1,1,0, 0,0,1,1,0,1,1,0, 0,0,1,1,0,1,0,0, 0,0,1,1,0,1,0,0, 0,0,0,1,0,0,0,0, 0,0,0,1,0,0,0,0, 1,5,6,1,0,0,0,0, 1,5,17,1,0,0,0,0, 1,5,20,1,0,0,0,0, 1,5,4,1,0,0,0,0, 1,5,4,0,0,0,0,0, 1,5,1,0,0,0,0,0, 1,5,1,0,0,0,0,0, 1,18,1,0,0,0,0,0, 0,0,0,0,1,5,1,0, 0,0,0,0,1,18,1,0, 0,0,0,0,1,18,1,0, 0,0,0,0,1,6,1,0, 0,0,0,0,1,4,1,0, 0,0,0,0,0,1,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,1,0,0,0,1,0, 0,0,1,0,0,0,1,0, 0,0,1,0,0,0,0,0, 0,0,1,0,0,0,0,0, 0,0,1,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,1,0,0,0,0, 0,0,0,1,0,0,0,0, 0,0,0,1,0,0,0,0, 0,0,0,1,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,21,1,0,0,0,0,0, 1,6,1,0,0,0,0,0, 1,17,1,0,0,0,0,0, 1,20,1,0,0,0,0,0, 1,4,1,0,0,0,0,0, 0,1,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 0,0,0,0,1,0,0,0, 0,0,0,1,10,1,0,0, 0,0,1,10,2,11,1,0, 0,1,10,24,22,11,9,1, 0,1,22,22,22,10,10,15, 0,1,8,8,8,11,9,1, 1,1,8,3,3,11,9,1, 3,1,1,10,10,11,9,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,0,0,0,0,0,0,0, 0,0,0,1,0,0,0,0, 0,0,1,10,1,0,0,0, 0,1,10,2,11,1,0,0, 1,10,24,22,11,9,1,0, 1,22,22,22,10,10,15,0, 1,8,8,8,11,9,1,0, 1,8,3,3,11,9,1,1, 1,8,10,15,11,1,1,3, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 0,0,0,0,0,0,1,7, 0,0,0,0,0,0,1,3, 0,0,0,0,0,1,7,3, 0,0,0,0,0,1,3,3, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,0,0,0,0,0,0,0, 7,1,1,0,0,0,0,0, 2,3,7,1,1,0,0,0, 8,2,2,3,7,1,1,0, 8,8,8,2,2,3,7,1, 0,0,0,0,0,0,0,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 0,0,0,0,0,0,0,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 3,2,3,1,1,1,9,1, 1,3,2,2,3,3,1,1, 1,1,1,3,2,2,2,2, 3,1,8,1,1,1,3,3, 3,2,1,10,7,15,1,1, 1,3,2,1,1,1,1,2, 0,1,3,2,2,2,2,3, 0,1,1,1,1,1,1,1, 3,1,0,0,0,0,0,0, 1,1,1,1,0,0,0,0, 3,3,3,3,1,1,1,1, 2,2,2,2,2,2,3,3, 1,1,1,1,3,3,2,2, 3,1,0,0,1,1,1,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,0,0,0,0,0,0, 3,3,1,1,1,1,1,1, 2,2,2,2,2,3,3,3, 1,1,3,3,3,2,2,2, 0,0,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,1,1, 1,1,1,1,1,1,3,3, 3,3,3,2,2,2,2,2, 2,2,2,3,3,3,1,1, 1,1,1,1,1,1,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,1,3, 0,0,0,0,1,1,1,1, 1,1,1,1,3,3,3,2, 3,2,2,2,2,2,2,3, 2,3,3,3,1,1,1,1, 1,1,1,1,0,0,1,3, 0,0,0,0,0,0,1,8, 0,0,0,0,0,0,0,1, 1,8,1,1,1,3,2,3, 1,1,3,3,2,2,3,1, 2,2,2,2,3,1,1,1, 3,3,1,1,1,1,1,3, 1,1,1,1,1,3,2,3, 1,1,3,2,2,2,3,1, 2,2,2,3,3,1,1,1, 3,3,1,1,1,9,1,3, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,0,0,0,0,0,0,0, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,0,0,0,0,0,0,0, 0,0,0,0,1,7,3,8, 0,0,0,0,1,3,8,8, 0,0,0,1,7,8,8,8, 0,0,0,1,3,8,8,9, 0,0,1,7,3,8,8,10, 0,0,1,3,8,8,8,8, 0,1,7,3,8,8,8,8, 0,1,3,8,8,8,8,8, 8,8,8,8,8,2,2,3, 8,8,8,8,8,8,8,2, 8,8,8,8,8,8,8,8, 9,9,9,10,3,8,8,8, 9,3,7,9,9,9,9,9, 10,9,3,2,2,2,2,2, 8,9,7,2,2,2,2,2, 8,10,9,7,2,2,2,2, 7,1,1,0,0,0,0,0, 2,3,7,1,1,0,0,0, 8,2,2,3,7,1,1,0, 8,8,8,2,2,3,7,1, 9,9,9,10,3,2,2,3, 2,3,7,9,9,9,9,2, 2,2,2,3,7,9,10,8, 2,3,7,9,9,10,8,8, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,0,0,0,0,0,0,0, 7,1,1,0,0,0,0,0, 2,3,7,1,1,0,0,0, 8,2,7,13,9,1,0,0, 8,7,13,13,9,1,0,0, 0,1,8,10,15,11,9,1, 0,1,1,15,11,11,9,1, 0,1,8,3,10,11,9,1, 0,1,8,10,7,11,1,3, 0,1,8,10,15,1,3,2, 0,1,8,10,1,3,2,1, 0,1,8,10,1,2,1,1, 0,1,8,10,1,2,1,1, 1,0,0,0,0,0,0,0, 3,1,0,0,0,0,0,0, 2,1,0,0,0,0,0,0, 2,1,0,0,0,0,0,0, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,10,15,1,3,2,3, 1,1,15,1,3,2,3,1, 1,7,15,1,2,3,1,0, 1,10,1,3,2,1,1,0, 1,3,1,2,3,1,1,0, 1,3,1,2,3,1,1,0, 1,3,1,2,3,1,1,0, 1,3,1,2,3,1,1,0, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,7,3,8,8,8,8,8, 1,7,10,10,3,8,8,8, 0,1,7,7,10,10,3,8, 0,0,1,1,11,7,10,10, 0,0,0,0,1,1,11,7, 0,0,0,0,0,0,1,1, 0,0,0,0,0,0,0,1, 0,0,0,0,0,0,0,1, 8,8,10,9,7,2,2,2, 8,8,8,10,9,3,2,2, 8,8,8,8,9,7,2,2, 3,8,8,8,10,9,7,2, 10,10,3,8,8,10,9,3, 11,7,10,10,3,8,10,9, 12,12,11,7,10,3,3,9, 12,12,12,12,11,7,10,10, 2,7,9,10,3,8,8,8, 2,9,10,8,8,8,8,8, 2,9,3,8,8,8,8,8, 3,9,8,8,8,8,8,7, 7,9,8,8,8,8,8,13, 9,10,8,8,8,8,7,13, 9,3,8,8,8,3,13,13, 9,8,8,8,8,7,13,13, 8,13,13,14,1,0,0,0, 7,13,13,9,1,0,0,0, 13,13,14,1,0,0,0,0, 13,13,9,1,0,0,0,0, 13,14,1,0,0,0,0,0, 13,9,1,0,0,0,0,0, 14,1,0,0,0,0,0,0, 9,1,0,0,0,0,0,0, 0,1,8,10,1,2,1,1, 0,1,8,10,1,3,2,1, 0,1,8,10,15,1,3,3, 0,1,1,15,11,11,1,1, 0,1,8,3,10,11,9,1, 0,1,8,10,7,11,9,1, 0,1,8,10,7,11,9,1, 0,1,8,10,7,11,9,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,0,0,0,0,0,0,0, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,3,11,3,2,1,1,0, 1,3,11,1,3,1,1,0, 1,3,10,11,1,1,1,0, 1,3,10,11,11,9,1,0, 1,3,10,11,11,9,1,0, 1,8,10,11,11,9,1,0, 1,8,10,15,11,9,1,0, 1,8,10,15,11,9,1,0, 0,0,0,0,0,0,1,9, 0,0,0,0,0,0,1,9, 0,0,0,0,0,1,14,14, 0,0,0,0,0,1,14,13, 0,0,0,0,1,14,14,15, 0,0,0,0,1,14,13,10, 0,0,0,1,14,14,15,10, 0,0,0,1,14,13,10,10, 9,14,14,14,12,12,11,7, 13,15,15,11,14,14,12,1, 15,7,7,15,11,13,14,1, 10,10,10,7,11,11,1,0, 10,3,3,10,15,11,1,0, 10,3,3,10,15,1,0,0, 3,8,3,15,15,1,0,0, 3,8,3,15,1,0,0,0, 10,3,8,3,3,13,13,14, 1,7,3,3,7,13,13,9, 0,1,1,7,13,13,14,1, 0,0,0,1,1,9,9,1, 0,0,0,0,0,1,1,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,0,0,0,0,0,0,0, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,1,1, 1,0,1,1,1,1,17,17, 6,1,6,6,5,18,18,18, 5,6,18,17,16,18,21,5, 16,5,18,4,5,23,21,5, 17,18,17,4,18,5,17,5, 4,17,4,4,17,18,17,18, 14,4,4,14,4,18,4,17, 0,0,0,1,1,1,1,0, 1,1,1,17,6,6,17,1, 18,17,5,18,5,18,6,18, 18,4,5,6,5,18,18,18, 17,4,17,17,16,18,18,6, 17,4,4,17,23,5,18,6, 17,4,13,17,16,23,18,17, 4,9,9,4,5,16,21,4, 0,0,0,0,0,0,1,1, 1,0,1,1,1,1,17,17, 6,1,6,6,5,18,18,18, 5,6,18,17,18,18,5,5, 16,5,18,18,5,18,18,5, 17,18,17,4,5,18,17,18, 4,17,4,4,5,18,17,18, 14,4,4,4,16,18,17,18, 0,0,0,1,1,1,1,0, 1,1,1,17,6,6,17,1, 18,18,5,18,5,18,6,18, 5,4,18,6,18,18,18,18, 5,18,18,5,18,18,18,6, 18,18,4,18,5,18,21,6, 17,4,13,17,5,18,21,6, 17,4,9,17,5,18,21,6, 0,0,1,1,1,1,1,0, 1,1,17,6,6,21,6,1, 6,5,6,18,18,6,5,18, 17,5,18,5,18,17,16,18, 17,16,16,5,18,17,5,17, 4,16,17,18,17,4,18,17, 4,18,4,17,4,4,17,4, 13,4,14,4,9,14,4,4, 0,1,8,10,7,11,9,1, 1,1,8,10,15,11,9,1, 6,1,8,10,7,11,9,1, 5,1,8,10,15,11,9,1, 5,4,1,1,1,1,1,5, 18,4,17,4,9,9,4,18, 17,4,4,4,9,9,4,6, 17,4,9,14,13,9,4,17, 0,1,1,1,1,1,1,0, 1,10,2,2,8,3,10,1, 1,8,3,7,7,7,7,1, 1,3,13,12,14,10,15,1, 1,7,11,10,8,3,11,1, 1,9,13,13,13,13,9,1, 4,1,1,1,1,1,1,0, 4,17,4,1,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,1,1,1,1,1,1,0, 1,10,2,2,8,3,10,1, 1,8,3,7,7,7,7,1, 1,3,13,12,14,10,15,1, 0,1,1,1,1,1,1,0, 1,10,2,2,8,3,10,1, 1,8,3,7,7,7,7,1, 1,3,13,12,14,10,15,1, 1,7,11,10,8,3,11,1, 1,9,13,13,13,13,9,1, 0,1,1,1,1,1,1,4, 0,0,0,1,17,20,4,1, 1,8,10,15,11,9,1,1, 1,8,10,15,11,9,1,17, 1,8,10,7,11,9,1,18, 1,8,10,15,11,9,1,5, 16,1,1,1,1,1,21,5, 17,18,17,4,18,5,17,5, 4,17,4,4,17,18,17,18, 14,4,4,14,4,18,4,17, 0,0,0,1,15,10,3,8, 1,0,1,1,1,15,3,3, 6,1,6,6,5,1,1,1, 5,6,18,17,16,18,21,5, 16,5,18,4,5,23,21,5, 17,18,17,4,18,5,17,5, 4,17,4,4,17,18,17,18, 14,4,4,14,4,18,4,17, 3,10,15,1,1,1,1,0, 10,1,1,17,6,6,17,1, 1,17,5,18,5,18,6,18, 18,4,5,6,5,18,18,18, 17,4,17,17,16,18,18,6, 17,4,4,17,23,5,18,6, 17,4,13,17,16,23,18,17, 4,9,9,4,5,16,21,4, 0,0,0,1,1,1,1,0, 1,1,1,17,6,6,17,1, 18,17,5,18,5,18,6,18, 18,4,5,6,5,18,18,18, 17,4,17,17,16,18,18,6, 17,4,4,17,16,18,21,6, 17,4,13,17,16,18,21,6, 4,9,9,17,16,18,21,6, 14,14,13,14,4,17,4,4, 10,15,15,15,4,17,4,14, 10,10,10,15,15,4,13,14, 10,10,10,10,15,15,11,7, 10,10,10,10,10,10,10,10, 10,10,10,10,10,10,10,10, 10,10,10,10,10,10,10,10, 10,10,10,10,10,10,10,10, 9,9,9,4,21,5,17,4, 14,13,14,4,17,17,4,9, 11,11,9,14,4,4,9,9, 11,11,13,13,13,13,13,13, 11,11,13,13,11,13,11,11, 11,11,11,13,11,11,11,11, 11,11,11,11,11,11,11,11, 11,11,11,11,11,11,11,11, 14,14,13,4,5,18,17,18, 10,15,15,4,16,18,17,18, 10,10,10,4,16,18,17,18, 10,10,10,4,16,18,17,18, 10,10,10,4,16,18,17,18, 10,10,10,4,16,18,17,18, 10,10,10,4,16,18,17,18, 10,10,10,4,16,18,17,18, 17,4,9,17,16,18,21,6, 17,4,14,17,5,18,21,6, 17,4,9,17,16,18,21,6, 17,4,13,17,16,18,21,6, 17,4,13,17,16,18,21,6, 17,4,11,17,16,18,21,6, 17,4,11,17,16,18,21,6, 17,4,11,17,16,18,21,6, 9,13,13,15,11,11,9,4, 9,13,7,7,10,7,9,13, 11,7,7,7,10,10,15,15, 10,7,7,10,10,10,10,15, 10,7,10,10,10,10,10,7, 10,10,10,10,10,10,10,10, 10,10,10,10,10,10,10,10, 10,10,10,10,10,10,10,10, 17,4,9,13,14,9,12,4, 4,9,9,13,14,9,12,1, 4,9,13,13,14,9,12,1, 13,13,11,13,14,9,12,1, 11,11,11,13,14,9,12,1, 11,11,11,13,14,9,12,1, 11,11,11,13,14,9,12,1, 11,11,11,13,14,9,12,1, 1,4,4,1,0,0,0,0, 0,1,1,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,7,11,10,8,3,11,1, 1,9,13,13,13,13,9,1, 0,1,1,1,1,1,1,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,1,4,4,1,0, 0,0,0,0,1,1,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,11,7,11,4,17,4,4, 1,7,3,3,4,17,4,14, 1,2,8,8,3,4,13,14, 1,2,2,8,10,15,11,7, 1,2,22,8,3,10,10,10, 1,2,22,8,3,10,10,10, 1,2,22,8,3,10,10,10, 1,2,22,8,3,10,10,10, 11,11,11,11,11,11,11,11, 11,11,11,11,11,11,11,11, 11,11,11,11,11,11,11,11, 11,11,11,11,11,11,11,11, 11,11,11,11,11,11,11,11, 11,11,11,11,11,11,11,11, 11,11,11,11,11,11,11,11, 11,11,11,11,11,11,11,11, 10,10,10,10,10,10,10,10, 10,10,10,10,10,10,10,10, 10,10,10,10,10,10,10,10, 10,10,10,10,10,10,10,10, 10,10,10,10,10,10,10,10, 10,10,10,10,10,10,10,10, 10,10,10,10,10,10,10,10, 10,10,10,10,10,10,10,10, 11,11,11,4,16,18,17,18, 11,11,11,4,16,18,17,18, 11,11,11,4,16,18,17,18, 11,11,11,4,16,18,17,18, 11,11,11,4,16,18,17,18, 11,11,11,4,16,18,17,18, 11,11,11,4,16,18,17,18, 11,11,11,4,16,18,17,18, 17,4,10,17,16,18,21,6, 17,4,10,17,16,18,21,6, 17,4,10,17,16,18,21,6, 17,4,10,17,16,18,21,6, 17,4,10,17,16,18,21,6, 17,4,10,17,16,18,21,6, 17,4,10,17,16,18,21,6, 17,4,10,17,16,18,21,6, 10,10,10,7,15,11,13,1, 10,10,10,7,15,11,13,1, 10,10,10,7,15,11,13,1, 10,10,10,7,15,11,13,1, 10,10,10,7,15,11,13,1, 10,10,10,7,15,11,13,1, 10,10,10,7,15,11,13,1, 10,10,10,7,15,11,13,1, 1,3,8,3,10,15,11,11, 1,3,8,3,10,15,11,11, 1,3,8,3,10,15,11,11, 1,3,8,3,10,15,11,11, 1,3,8,3,10,15,11,11, 1,3,8,3,10,15,11,11, 1,3,8,3,10,15,11,11, 1,3,8,3,10,15,11,11, 10,10,10,4,16,18,17,18, 10,10,10,4,16,18,17,18, 10,10,10,4,16,18,17,18, 10,10,10,4,16,18,17,18, 10,10,10,4,16,18,17,18, 10,10,10,4,16,18,17,18, 10,10,10,4,16,18,17,18, 10,10,10,4,16,18,17,18, 17,4,11,17,16,18,21,6, 17,4,11,17,16,18,21,6, 17,4,11,17,16,18,21,6, 17,4,11,17,16,18,21,6, 17,4,11,17,16,18,21,6, 17,4,11,17,16,18,21,6, 17,4,11,17,16,18,21,6, 17,4,11,17,16,18,21,6, 11,11,11,13,14,9,12,1, 11,11,11,13,14,9,12,1, 11,11,11,13,14,9,12,1, 11,11,11,13,14,9,12,1, 11,11,11,13,14,9,12,1, 11,11,11,13,14,9,12,1, 11,11,11,13,14,9,12,1, 11,11,11,13,14,9,12,1, 1,2,22,8,3,10,10,10, 1,2,22,8,3,10,10,10, 1,2,22,8,3,10,10,10, 1,2,22,8,3,10,10,10, 1,2,22,8,3,10,10,10, 1,2,22,8,3,10,10,10, 1,2,22,8,3,10,10,10, 1,2,22,8,3,10,10,10, 17,4,10,17,16,18,21,6, 17,4,10,17,23,18,21,6, 17,4,10,17,23,5,21,6, 17,4,10,17,16,23,21,17, 17,4,10,4,5,16,21,4, 17,4,10,4,21,5,17,4, 17,4,10,10,17,17,4,10, 17,4,10,10,10,10,10,10, 10,10,10,4,16,18,17,18, 10,10,10,4,16,5,17,18, 10,10,10,4,16,5,17,4, 10,10,10,4,23,16,4,10, 10,10,10,4,23,16,4,10, 10,10,10,4,5,18,4,10, 10,10,10,4,17,17,4,10, 10,10,10,10,4,4,10,10, 17,4,11,11,11,11,11,11, 17,4,11,11,11,11,11,11, 4,11,11,11,11,11,11,11, 11,11,11,11,11,11,11,11, 11,11,11,11,11,11,11,11, 11,11,11,11,11,11,11,11, 11,11,11,11,11,11,11,11, 11,11,11,11,11,11,11,11, 19,2,22,8,3,10,10,10, 19,2,22,8,3,10,10,10, 19,2,22,8,3,10,10,10, 19,2,22,8,3,10,10,10, 19,2,22,8,3,10,10,10, 19,2,22,8,3,10,10,10, 19,2,22,8,3,10,10,10, 19,2,22,8,3,10,10,10, 10,10,7,15,13,1,1,1, 10,7,1,4,18,18,17,4, 15,1,4,5,17,5,5,18, 13,4,5,18,4,5,18,18, 1,4,5,4,5,17,4,17, 1,4,17,4,5,4,9,17, 9,1,4,9,17,4,9,9, 14,14,9,14,4,9,14,14, 1,1,1,1,1,1,19,19, 19,1,19,19,19,19,17,17, 6,19,6,6,5,18,18,18, 5,6,18,17,16,18,21,5, 16,5,18,4,5,23,21,5, 17,18,17,4,18,5,17,5, 4,17,4,4,17,18,17,18, 14,4,4,14,4,18,4,17, 1,1,1,19,19,19,19,1, 19,19,19,17,6,6,17,19, 18,17,5,18,5,18,6,18, 18,4,5,6,5,18,18,18, 17,4,17,17,16,18,18,6, 17,4,4,17,23,5,18,6, 17,4,13,17,16,23,18,17, 4,9,9,4,5,16,21,4, 0,0,0,1,1,1,1,0, 1,1,1,17,6,6,17,1, 18,17,5,18,5,18,6,18, 5,17,5,17,4,17,18,5, 5,4,18,17,4,4,17,5, 18,4,17,4,9,9,4,18, 17,4,4,4,9,9,4,6, 17,4,4,1,14,9,4,17, 0,0,1,1,1,1,1,0, 1,1,1,17,17,1,1,1, 6,5,18,18,18,18,17,5, 17,16,18,21,5,18,4,5, 4,5,23,21,5,17,4,17, 4,18,5,17,5,17,4,4, 4,17,18,17,18,17,4,13, 14,4,18,4,17,4,9,9, 1,1,1,1,0,0,0,0, 17,6,6,17,1,1,0,1, 18,5,18,6,18,6,1,6, 6,5,18,18,18,5,6,18, 17,16,18,18,6,16,5,18, 17,23,5,18,6,17,18,17, 17,16,23,18,17,4,17,4, 4,5,16,21,4,14,4,4, 0,0,0,1,1,0,0,0, 1,1,1,17,17,1,1,1, 6,5,18,18,18,18,17,5, 17,16,18,21,5,18,4,5, 4,5,23,21,5,17,4,17, 4,18,5,17,5,17,4,4, 4,17,18,17,18,17,4,13, 14,4,18,4,17,4,9,9, 1,1,1,1,1,1,1,0, 17,1,1,17,6,6,17,1, 18,17,5,18,5,18,6,18, 6,4,5,6,5,18,18,18, 17,4,17,17,16,18,18,6, 17,4,4,17,23,5,18,6, 17,4,13,17,16,23,18,17, 4,9,9,4,5,16,21,4, 0,0,0,1,1,0,1,1, 1,1,1,1,1,1,17,17, 6,1,6,6,5,18,18,18, 5,6,18,17,18,18,5,5, 16,5,18,18,5,18,18,5, 17,18,17,4,5,18,17,18, 4,17,4,4,5,18,17,18, 14,4,4,4,16,18,17,18, 0,0,0,1,1,1,1,1, 1,1,1,17,6,6,17,1, 18,18,5,18,5,18,6,18, 5,4,18,6,18,18,18,18, 5,18,18,5,18,18,18,6, 18,18,4,18,5,18,21,6, 17,4,13,17,5,18,21,6, 17,4,9,17,5,18,21,6, 19,19,19,19,9,11,11,11, 4,17,18,18,4,19,11,11, 18,5,5,17,5,4,19,11, 18,18,5,4,18,5,4,9, 17,4,17,5,4,5,4,19, 17,9,4,5,4,17,4,19, 9,9,4,17,9,4,19,9, 14,14,9,4,14,9,14,14, 11,11,11,14,9,14,11,11, 11,11,11,11,14,11,11,11, 11,11,11,11,11,11,11,11, 11,11,11,11,11,11,11,11, 11,11,11,11,11,11,11,11, 11,11,11,11,11,11,11,11, 11,11,11,11,11,11,11,11, 11,11,11,11,11,11,11,11, 19,11,7,11,4,17,4,4, 19,7,3,3,4,17,4,14, 19,2,8,8,3,4,13,14, 19,2,2,8,10,15,11,7, 19,2,22,8,3,10,10,10, 19,2,22,8,3,10,10,10, 19,2,22,8,3,10,10,10, 19,2,22,8,3,10,10,10, 14,14,13,14,4,17,4,4, 10,10,14,1,4,17,4,1, 10,10,11,1,1,4,1,1, 10,10,7,14,1,1,1,1, 10,10,10,7,14,1,1,1, 10,10,10,10,7,11,14,9, 10,10,10,10,10,10,3,3, 10,10,10,10,10,10,10,10, 17,4,1,1,9,9,9,4, 4,1,1,1,9,3,9,9, 4,1,1,1,14,8,11,11, 1,1,1,9,7,8,11,11, 1,1,9,11,2,7,11,11, 9,14,7,22,3,15,11,11, 8,8,2,7,15,11,11,11, 11,11,11,11,11,11,11,11, 14,4,17,4,4,9,9,9, 15,4,17,4,14,14,13,14, 15,15,4,13,14,11,11,9, 10,15,15,11,7,11,11,13, 10,10,10,10,10,11,11,13, 10,10,10,10,10,11,11,11, 10,10,10,10,10,11,11,11, 10,10,10,10,10,11,11,11, 4,21,5,17,4,14,14,13, 4,17,17,4,9,10,15,15, 14,4,4,9,9,10,10,10, 13,13,13,13,13,10,10,10, 13,11,13,11,11,10,10,10, 13,11,11,11,11,10,10,10, 11,11,11,11,11,10,10,10, 11,11,11,11,11,10,10,10, 4,9,9,4,21,5,17,4, 4,13,14,4,17,17,4,9, 14,11,9,14,4,4,9,9, 13,11,13,13,13,13,13,13, 13,11,13,13,11,13,11,11, 13,11,11,13,11,11,11,11, 11,11,11,11,11,11,11,11, 11,11,11,11,11,11,11,11, 11,15,14,14,14,14,11,15, 15,7,11,14,11,11,15,10, 7,10,7,11,7,7,10,10, 10,10,10,7,7,10,10,10, 10,10,10,10,10,10,10,10, 10,10,10,10,10,10,10,10, 10,10,10,10,10,10,10,10, 10,10,10,10,10,10,10,10, 
};
