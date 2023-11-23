#define MAX_BALLS 100
#define DAMPING 0.9
#define GRAVITY 0.8
#define SPEED 1
#define TWO_PI (3.14159 * 2)

using Fract = SQ15x16;
int numBalls = 0;

typedef struct {
    Fract x, y;
    Fract px, py;
    Fract fx, fy;
    int radius;
    int frameNumber;
} Ball;

Ball balls[MAX_BALLS];
int ballRad[] = {7,10,12,15,17,20,22,25,27,30,32,35};

int canvasWidth = 220;
int canvasHeight = 176;

void applyForce(Ball *ball, Fract delta) {
    delta *= delta;

    ball->fy += GRAVITY;

    ball->x += ball->fx * delta;
    ball->y += ball->fy * delta;

    ball->fx = ball->fy = 0;
    
}

void verlet(Ball *ball) {
    Fract nx = (ball->x * 2) - ball->px;
    Fract ny = (ball->y * 2) - ball->py;

    ball->px = ball->x;
    ball->py = ball->y;

    ball->x = nx;
    ball->y = ny;
}


void drawBall(Ball *ball) {
    char tempText[5];
    sprintf(tempText,"%d",int(ball->frameNumber));

    int bx = static_cast<float>(ball->x - ball->radius);
    int by = static_cast<float>(ball->y - ball->radius);

    switch(ball->frameNumber){
        case 0:
            drawSprite(bx, by, joe_01, 128, 8);
            break;
        case 1:
            drawSprite(bx, by, joe_02, 128, 8);
            break;
        case 2:
            drawSprite(bx, by, joe_03, 128, 8);
            break;
        case 3:
            drawSprite(bx, by, joe_04, 128, 8);
            break;
        case 4:
            drawSprite(bx, by, joe_05, 128, 8);
            break;
        case 5:
            drawSprite(bx, by, joe_06, 128, 8);
            break;
        case 6:
            drawSprite(bx, by, joe_07, 128, 8);
            break;
        case 7:
            drawSprite(bx, by, joe_08, 128, 8);
            break;
        case 8:
            drawSprite(bx, by, joe_09, 128, 8);
            break;
        case 9:
            drawSprite(bx, by, joe_10, 128, 8);
            break;
        case 10:
            drawSprite(bx, by, joe_11, 128, 8);
            break;
        case 11:
            drawSprite(bx, by, joe_12, 128, 8);
            break;
    }
//    myPrint(ball->x -4, ball->y -4,tempText);
}


void resolveCollisions(int ip) {
    int i, n;
    Fract diff_x, diff_y, dist, real_dist, depth_x, depth_y;
    Ball *ball_1, *ball_2;
    i = numBalls;

    int ballChecked[numBalls];
    for(int t=0; t<numBalls; t++){
        ballChecked[t]=0;
    }

    while (i--) {
        ball_1 = &balls[i];

        n = numBalls;

        while (n--) {
            if (n == i)
                continue;
            
            // if this ball has already checked its surrounding balls, don't do it again.
            if(ballChecked[n])
                continue;

            ball_2 = &balls[n];

            diff_x = ball_1->x - ball_2->x;
            diff_y = ball_1->y - ball_2->y;

            if(diff_x > 35 || diff_y > 35)
                continue;

            int length = static_cast<float>(diff_x * diff_x + diff_y * diff_y);
            dist = sqrt(int(length));
            real_dist = dist - (ball_1->radius + ball_2->radius);

            if (real_dist < 0) {
                Fract vel_x1 = ball_1->x - ball_1->px;
                Fract vel_y1 = ball_1->y - ball_1->py;
                Fract vel_x2 = ball_2->x - ball_2->px;
                Fract vel_y2 = ball_2->y - ball_2->py;

                depth_x = diff_x * (real_dist / dist);
                depth_y = diff_y * (real_dist / dist);

                ball_1->x -= depth_x * 0.5;
                ball_1->y -= depth_y * 0.5;
                
                ball_2->x += depth_x * 0.5;
                ball_2->y += depth_y * 0.5;

                if (ip) {
                    Fract pr1 = DAMPING * (diff_x * vel_x1 + diff_y * vel_y1) / length;
                    Fract pr2 = DAMPING * (diff_x * vel_x2 + diff_y * vel_y2) / length;

                    vel_x1 += pr2 * diff_x - pr1 * diff_x;
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
        ballChecked[i]=1;
    }
}

void check_walls() {
    int i;
    for (i = 0; i < numBalls; i++) {
        Ball *ball = &balls[i];

        if (ball->x < ball->radius) {
            Fract vel_x = ball->px - ball->x;
            ball->x = ball->radius;
            ball->px = ball->x - vel_x * DAMPING;
        } else if (ball->x + ball->radius > canvasWidth) {
            Fract vel_x = ball->px - ball->x;
            ball->x = canvasWidth - ball->radius;
            ball->px = ball->x - vel_x * DAMPING;
        }

        if (ball->y < ball->radius) {
            Fract vel_y = ball->py - ball->y;
            ball->y = ball->radius;
            ball->py = ball->y - vel_y * DAMPING;
        } else if (ball->y + ball->radius > canvasHeight) {
            Fract vel_y = ball->py - ball->y;
            ball->y = canvasHeight - ball->radius;
            ball->py = ball->y - vel_y * DAMPING;
        }
    }
}

void updateBalls() {
    int i;
    int delta = 1;  // Change this value based on your desired time step

    for (i = 0; i < numBalls; i++) {
        Ball *ball = &balls[i];

        applyForce(ball, delta);
        verlet(ball);
        resolveCollisions(i);
        check_walls();        

        drawBall(ball);
    }
}


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

