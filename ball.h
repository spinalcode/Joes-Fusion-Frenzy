
using Fract = SQ15x16;

inline void applyForce(Ball *ball, Fract delta) {
    //delta *= delta;

    ball->fy += GRAVITY;

    ball->x += ball->fx * (delta * delta);
    ball->y += ball->fy * (delta * delta);

    ball->fx = ball->fy = 0;
}

inline void verlet(Ball* ball) {
    Fract nx = (ball->x * 2) - ball->px;
    Fract ny = (ball->y * 2) - ball->py;

    ball->px = ball->x;
    ball->py = ball->y;


    //nx = ball->x + 0.95) * (nx - ball->x);
    nx = ball->x + float(0.23 * DELTA) * (nx - ball->x);

    if (ny < ball->y)
        ny = ball->y;// + 0.99 * (ny - ball->y);

    ball->x = nx;
    ball->y = ny;
}

void drawBalls(){
    for (int i = 0; i < numBalls; i++) {
        Ball *ball = &balls[i];
        drawMaskedSprite(static_cast<float>(ball->x - ball->radius), static_cast<float>(ball->y - ball->radius), spriteFrameData[ball->frameNumber], spritePalData[ball->frameNumber],spriteMaskData[ball->frameNumber], 8);
    }    
}

void drawBalls2(int i, int n){
    for (int t = 0; t < numBalls; t++) {
        Ball *ball = &balls[t];
        if(i==t || n==t){
            drawMaskedSprite(static_cast<float>(ball->x - ball->radius), static_cast<float>(ball->y - ball->radius), spriteFrameData[ball->frameNumber], greyscale_pal,spriteMaskData[ball->frameNumber], 8);
        }else{
            drawMaskedSprite(static_cast<float>(ball->x - ball->radius), static_cast<float>(ball->y - ball->radius), spriteFrameData[ball->frameNumber], spritePalData[ball->frameNumber],spriteMaskData[ball->frameNumber], 8);
        }
    }    
}


inline void resolveCollisions(int ip) {
    Fract diff_x, diff_y, dist, real_dist, depth_x, depth_y;
    Ball *ball_1, *ball_2;

    for (int i = 1; i < numBalls; i++) {
        ball_1 = &balls[i];
        for (int n = 0; n < i; n++) {
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
/*
                printf("b1=%d, b2=%d, Num=%d\n",i,n, numBalls);
                spriteCount=0;
                drawBalls();
                int counter=0;
                while (!_B_But[HELD]){
                    updateButtons();
                    Pokitto::Core::update();
                    spriteCount=0;
                    if(++counter==2){
                        drawBalls2(i,n);
                        counter=0;
                    }else{
                        drawBalls();
                    }
                }
                while (_B_But[HELD]){ updateButtons(); }
*/

                int tx1 = ball_1->x.getInteger();
                int ty1 = ball_1->y.getInteger();
                int tfn = ball_1->frameNumber;
                int tx2 = ball_2->x.getInteger();
                int ty2 = ball_2->y.getInteger();

                startExplosion(static_cast<float>(ball_1->x - ball_1->radius), static_cast<float>(ball_1->y - ball_1->radius), ball_1->frameNumber);
                startExplosion(static_cast<float>(ball_2->x - ball_2->radius), static_cast<float>(ball_2->y - ball_2->radius), ball_2->frameNumber);
                
                int number = random(4);
                Pokitto::Sound::playSFX( sfx_pop[number], sfx_pop_size[number] );

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

                newBallX = (tx1+tx2)/2;
                newBallY = (ty1+ty2)/2;
                newBallFrame = tfn+1;
                newBallRad = ballRad[newBallFrame];
                    
                //continue;
                return;
            }
        }
    }
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

    if(stillAnimating==false){

        for (int i = 0; i < numBalls; i++) {
            Ball *ball = &balls[i];
            applyForce(ball, 1);
            verlet(ball);
        }
    
        resolveCollisions(0);
        check_walls();
    
        for (int i = 0; i < numBalls; i++) {
            Ball *ball = &balls[i];
            verlet(ball);
        }
        resolveCollisions(1);
        check_walls();
    }
}
