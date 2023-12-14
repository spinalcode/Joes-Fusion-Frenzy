#define MAX_BALLS 100
#define DAMPING 0.001
#define GRAVITY 0.25
#define SPEED 1
#define TWO_PI (3.14159 * 2)

using Fract = SQ15x16;
int numBalls = 0;

typedef struct {
    Fract x, y;
    Fract px, py;
    Fract fx, fy;
    Fract grav;
    int radius;
    uint8_t frameNumber;
} Ball;

Ball balls[MAX_BALLS];
const uint8_t ballRad[] = {4,5,7,8,11,14,16,19,22,27,32};
const Fract ballGrav[] = {0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09, 0.10, 0.11};

uint8_t quad[4][MAX_BALLS];
uint8_t qCount[4];

#define canvasLeft 47
#define canvasRight 152
#define canvasBottom 162


void newBall(int x, int y, int cb){
    balls[numBalls].x = x;
    balls[numBalls].y = y;
    balls[numBalls].px = x;
    balls[numBalls].py = y;
    balls[numBalls].fx = 0;
    balls[numBalls].fy = 0;
    balls[numBalls].frameNumber = cb;
    balls[numBalls].radius = ballRad[balls[numBalls].frameNumber];
    numBalls++;
}

inline void applyForce(Ball *ball, Fract delta) {
    //delta *= delta;

    ball->fy += ball->grav;

    ball->x += ball->fx * delta;
    ball->y += ball->fy * delta;

    ball->fx = ball->fy = 0;
}

inline void verlet(Ball *ball) {
    Fract nx = (ball->x * 2) - ball->px;
    Fract ny = (ball->y * 3) - ball->py;

    ball->px = ball->x;
    ball->py = ball->y;

    ball->x = nx;
    ball->y = ny;
}


inline void resolveCollisions(int ip) {
    Fract diff_x, diff_y, dist, real_dist, depth_x, depth_y;
    Ball *ball_1, *ball_2;

    for (int i = 1; i < numBalls; ++i) {
        ball_1 = &balls[i];
        for (int n = 0; n < i; ++n) {
            ball_2 = &balls[n];

            diff_x = ball_1->x - ball_2->x;
            diff_y = ball_1->y - ball_2->y;

            if(diff_x > 35 || diff_y > 35 || diff_x < -35 || diff_y < -35)
                continue;

            int length = (diff_x * diff_x + diff_y * diff_y).getInteger();
            int radius = ball_1->radius + ball_2->radius;
            int radius2 = radius * radius;

            if (length > radius2)
                continue;
            dist = sqrt(length);
            real_dist = dist - radius;
            Fract vel_x1 = ball_1->x - ball_1->px;
            Fract vel_y1 = ball_1->y - ball_1->py;
            Fract vel_x2 = ball_2->x - ball_2->px;
            Fract vel_y2 = ball_2->y - ball_2->py;

            depth_x = diff_x * (real_dist / dist);
            depth_y = diff_y * (real_dist / dist);

            ball_1->x -= depth_x / 2 ;
            ball_1->y -= depth_y / 2;
                
            ball_2->x += depth_x / 2;
            ball_2->y += depth_y / 2;
        }
    }
}


inline void resolveCollisions2(int ip) {
    Fract diff_x, diff_y, dist, real_dist, depth_x, depth_y;
    Ball *ball_1, *ball_2;

    //for(int q=0; q<4; q++){

        //for (int i = 1; i < qCount[q]; ++i) {
        for (int i = 1; i < numBalls; ++i) {
            //ball_1 = &balls[quad[q][i]];
            ball_1 = &balls[i];
            for (int n = 0; n < i; ++n) {
                //ball_2 = &balls[quad[q][n]];
                ball_2 = &balls[n];
    
                diff_x = ball_1->x - ball_2->x;
                diff_y = ball_1->y - ball_2->y;
    
                if(diff_x > 35 || diff_y > 35 || diff_x < -35 || diff_y < -35)
                    continue;
    
                int length = (diff_x * diff_x + diff_y * diff_y).getInteger();
                int radius = ball_1->radius + ball_2->radius;
                int radius2 = radius * radius;
    
                if (length > radius2)
                    continue;

                dist = sqrt(length);
                real_dist = dist - radius;
                Fract vel_x1 = ball_1->x - ball_1->px;
                Fract vel_y1 = ball_1->y - ball_1->py;
                Fract vel_x2 = ball_2->x - ball_2->px;
                Fract vel_y2 = ball_2->y - ball_2->py;
    
                depth_x = diff_x * (real_dist / dist);
                depth_y = diff_y * (real_dist / dist);
    
                ball_1->x -= depth_x / 2 ;
                ball_1->y -= depth_y / 2;
                    
                ball_2->x += depth_x / 2;
                ball_2->y += depth_y / 2;

                if(ball_1->radius == ball_2->radius){

                    //printf("b1=%d, b2=%d\n",i,n);

                    int tx1 = ball_1->x.getInteger();
                    int ty1 = ball_1->y.getInteger();
                    int tfn = ball_1->frameNumber;
                    int tx2 = ball_2->x.getInteger();
                    int ty2 = ball_2->y.getInteger();

                    // remove each ball by bumping everything up the queue
                    for (int p = i; p < numBalls-1; p++) {
                        balls[p].x = balls[p+1].x;
                        balls[p].y = balls[p+1].y;
                        balls[p].px = balls[p+1].px;
                        balls[p].py = balls[p+1].py;
                        balls[p].fx = balls[p+1].fx;
                        balls[p].fy = balls[p+1].fy;
                        balls[p].frameNumber = balls[p+1].frameNumber;
                        balls[p].radius = balls[p+1].radius;
                    }
                    numBalls--;
                    for (int p = n; p < numBalls-1; p++) {
                        balls[p].x = balls[p+1].x;
                        balls[p].y = balls[p+1].y;
                        balls[p].px = balls[p+1].px;
                        balls[p].py = balls[p+1].py;
                        balls[p].fx = balls[p+1].fx;
                        balls[p].fy = balls[p+1].fy;
                        balls[p].frameNumber = balls[p+1].frameNumber;
                        balls[p].radius = balls[p+1].radius;
                    }
                    numBalls--;
                    // create a new ball in their place
                    //newBall((tx1+tx2)/2, (ty1+ty2)/2, tfn+1);
                    balls[numBalls].x = (tx1+tx2)/2;
                    balls[numBalls].y = (ty1+ty2)/2;
                    balls[numBalls].px = (tx1+tx2)/2;
                    balls[numBalls].py = (ty1+ty2)/2;
                    balls[numBalls].fx = 0;
                    balls[numBalls].fy = 0;
                    balls[numBalls].frameNumber = tfn+1;
                    balls[numBalls].radius = ballRad[balls[numBalls].frameNumber];
                    numBalls++;

                    return;
                    //continue;
                }
                if (ip) {
                    
                    Fract pr1 = DAMPING * (diff_x * vel_x1 + diff_y * vel_y1) / length;
                    Fract pr2 = DAMPING * (diff_x * vel_x2 + diff_y * vel_y2) / length;

                    vel_x1 += (pr2 * diff_x - pr1 * diff_x)/2;
                    vel_x2 += pr1 * diff_x - pr2 * diff_x;

                    vel_y1 += pr2 * diff_y - pr1 * diff_y;
                    vel_y2 += pr1 * diff_y - pr2 * diff_y;

                    ball_1->px = ball_1->x - vel_x1;
                    ball_1->py = ball_1->y - vel_y1;

                    ball_2->px = ball_2->x - vel_x2;
                    ball_2->py = ball_2->y - vel_y2;

                }
                
            }
        }
    //}
}


inline void check_walls() {
    int i;
    for (i = 0; i < numBalls; i++) {
        Ball *ball = &balls[i];

        if (ball->x - ball->radius < canvasLeft) {
            Fract vel_x = ball->px - ball->x;
            ball->x = canvasLeft + ball->radius;
            ball->px = ball->x - vel_x * DAMPING;
        } else if (ball->x + ball->radius > canvasRight) {
            Fract vel_x = ball->px - ball->x;
            ball->x = canvasRight - ball->radius;
            ball->px = ball->x - vel_x * DAMPING;
        }

        if (ball->y < ball->radius) {
            Fract vel_y = ball->py - ball->y;
            ball->y = ball->radius;
            ball->py = ball->y - vel_y * DAMPING;
        } else if (ball->y + ball->radius > canvasBottom) {
            Fract vel_y = ball->py - ball->y;
            ball->y = canvasBottom - ball->radius;
            ball->py = ball->y - vel_y * DAMPING;
        }
    }
}

void updateBalls(bool frm) {

    qCount[0]=0;
    qCount[1]=0;
    qCount[2]=0;
    qCount[3]=0;
    
    #define MIDWIDTH 110    
    #define MIDHEIGHT 88    
    
    for (int i = 0; i < numBalls; i++) {
        if(balls[i].x < MIDWIDTH + 36){
            if(balls[i].y < MIDHEIGHT + 36){
                quad[0][qCount[0]++] = i;
            }
            if(balls[i].y > MIDHEIGHT - 36){
                quad[2][qCount[2]++] = i;
            }
        }
        if(balls[i].x > MIDWIDTH - 36){
            if(balls[i].y < MIDHEIGHT + 36){
                quad[1][qCount[1]++] = i;
            }
            if(balls[i].y > MIDHEIGHT - 36){
                quad[3][qCount[3]++] = i;
            }
        }        
    }

    int i;
    int delta = 1;  // Change this value based on your desired time step

    for(int s=0; s<3; s++){
        for (i = 0; i < numBalls; i++) {
            Ball *ball = &balls[i];
            applyForce(ball, delta);
            verlet(ball);
        }
    
        resolveCollisions2(0);
        check_walls();
    
        for (i = 0; i < numBalls; i++) {
            Ball *ball = &balls[i];
            verlet(ball);
        }
    
        resolveCollisions2(1);
        check_walls();
    }
    
    for (i = 0; i < numBalls; i++) {
        Ball *ball = &balls[i];
        drawMaskedSprite(static_cast<float>(ball->x - ball->radius), static_cast<float>(ball->y - ball->radius), spriteFrameData[ball->frameNumber], spritePalData[ball->frameNumber],spriteMaskData[ball->frameNumber], 8);
    }
}

/*
void initBalls(){
    int i;
    for (i = 0; i < numBalls; i++) {
        balls[i].x = (rand() % canvasWidth);
        balls[i].y = (rand() % canvasHeight);
        balls[i].px = balls[i].x;
        balls[i].py = balls[i].y;
        balls[i].fx = 0;
        balls[i].fy = 0;
        balls[i].frameNumber = rand() % 12;
        balls[i].radius = ballRad[balls[i].frameNumber];//rand() % 20 + 10;
    }
}
*/
