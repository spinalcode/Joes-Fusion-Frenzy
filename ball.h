#define NUM_BALLS 10
#define DAMPING 0.7
#define GRAVITY 0.6
#define MOUSE_SIZE 5
#define SPEED 1
#define TWO_PI (3.14159 * 2)

typedef struct {
    float x, y;
    float px, py;
    float fx, fy;
    float radius;
    int frameNumber;
} Ball;

Ball balls[NUM_BALLS];
int ballRad[] = {7,10,12,15,17,20,22,25,27,30,32,35};

int canvasWidth = 220;
int canvasHeight = 176;

void applyForce(Ball *ball, float delta) {
    delta *= delta;

    ball->fy += GRAVITY;

    ball->x += ball->fx * delta;
    ball->y += ball->fy * delta;

    ball->fx = ball->fy = 0;
    
    char tempText[64];
    sprintf(tempText,"%d",int(ball->y) >> 8);
    myPrint(110,8,tempText);
    
}

void verlet(Ball *ball) {
    float nx = (ball->x * 2) - ball->px;
    float ny = (ball->y * 2) - ball->py;

    ball->px = ball->x;
    ball->py = ball->y;

    ball->x = nx;
    ball->y = ny;
}


void drawBall(Ball *ball) {
    switch(ball->frameNumber){
        case 0:
            drawSprite(ball->x - ball->radius, ball->y - ball->radius, joe_01, 128, 8);
            break;
        case 1:
            drawSprite(ball->x - ball->radius, ball->y - ball->radius, joe_02, 128, 8);
            break;
        case 2:
            drawSprite(ball->x - ball->radius, ball->y - ball->radius, joe_03, 128, 8);
            break;
        case 3:
            drawSprite(ball->x - ball->radius, ball->y - ball->radius, joe_04, 128, 8);
            break;
        case 4:
            drawSprite(ball->x - ball->radius, ball->y - ball->radius, joe_05, 128, 8);
            break;
        case 5:
            drawSprite(ball->x - ball->radius, ball->y - ball->radius, joe_06, 128, 8);
            break;
        case 6:
            drawSprite(ball->x - ball->radius, ball->y - ball->radius, joe_07, 128, 8);
            break;
        case 7:
            drawSprite(ball->x - ball->radius, ball->y - ball->radius, joe_08, 128, 8);
            break;
        case 8:
            drawSprite(ball->x - ball->radius, ball->y - ball->radius, joe_09, 128, 8);
            break;
        case 9:
            drawSprite(ball->x - ball->radius, ball->y - ball->radius, joe_10, 128, 8);
            break;
        case 10:
            drawSprite(ball->x - ball->radius, ball->y - ball->radius, joe_11, 128, 8);
            break;
        case 11:
            drawSprite(ball->x - ball->radius, ball->y - ball->radius, joe_12, 128, 8);
            break;
    }
}


void resolveCollisions(int ip) {
    int i, n;
    float diff_x, diff_y, dist, real_dist, depth_x, depth_y;
    Ball *ball_1, *ball_2;
    i = NUM_BALLS;

    while (i--) {
        ball_1 = &balls[i];

        n = NUM_BALLS;

        while (n--) {
            if (n == i)
                continue;

            ball_2 = &balls[n];

            diff_x = ball_1->x - ball_2->x;
            diff_y = ball_1->y - ball_2->y;

            float length = diff_x * diff_x + diff_y * diff_y;
            dist = sqrt(length);
            real_dist = dist - (ball_1->radius + ball_2->radius);

            if (real_dist < 0) {
                float vel_x1 = ball_1->x - ball_1->px;
                float vel_y1 = ball_1->y - ball_1->py;
                float vel_x2 = ball_2->x - ball_2->px;
                float vel_y2 = ball_2->y - ball_2->py;

                depth_x = diff_x * (real_dist / dist);
                depth_y = diff_y * (real_dist / dist);

                ball_1->x -= depth_x * 0.5;
                ball_1->y -= depth_y * 0.5;
                
                ball_2->x += depth_x * 0.5;
                ball_2->y += depth_y * 0.5;

                if (ip) {
                    float pr1 = DAMPING * (diff_x * vel_x1 + diff_y * vel_y1) / length;
                    float pr2 = DAMPING * (diff_x * vel_x2 + diff_y * vel_y2) / length;

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
    }
}

void check_walls() {
    int i;
    for (i = 0; i < NUM_BALLS; i++) {
        Ball *ball = &balls[i];

        if (ball->x < ball->radius) {
            float vel_x = ball->px - ball->x;
            ball->x = ball->radius;
            ball->px = ball->x - vel_x * DAMPING;
        } else if (ball->x + ball->radius > canvasWidth) {
            float vel_x = ball->px - ball->x;
            ball->x = canvasWidth - ball->radius;
            ball->px = ball->x - vel_x * DAMPING;
        }

        if (ball->y < ball->radius) {
            int vel_y = ball->py - ball->y;
            ball->y = ball->radius;
            ball->py = ball->y - vel_y * DAMPING;
        } else if (ball->y + ball->radius > canvasHeight) {
            int vel_y = ball->py - ball->y;
            ball->y = canvasHeight - ball->radius;
            ball->py = ball->y - vel_y * DAMPING;
        }
    }
}

void updateBalls() {
    int i;
    int delta = 1;  // Change this value based on your desired time step

    for (i = 0; i < NUM_BALLS; i++) {
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
    for (i = 0; i < NUM_BALLS-1; i++) {
        balls[i].x = (rand() % canvasWidth);
        balls[i].y = (rand() % canvasHeight);
        balls[i].px = balls[i].x;
        balls[i].py = balls[i].y;
        balls[i].radius = ballRad[i];//rand() % 20 + 10;
        balls[i].fx = 0;
        balls[i].fy = 0;
        balls[i].frameNumber = i;
    }
}

