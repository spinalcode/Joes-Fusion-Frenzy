#define MAX_BALLS 100
#define W 104
#define H 176
#define L 49

using Fract = SQ15x16;

Fract bounce = 0.7;

typedef struct {
    Fract x;
    Fract y;
    Fract dx;
    Fract dy;
    Fract r;
    char color[20];
    char frameNumber;
} Ball;

const uint8_t ballRad[] = {4,5,7,8,11,14,16,19,22,27,32};

int numBalls = 1;
Fract grav[2] = {0, -0.1};

Ball balls[MAX_BALLS];


void update(Ball* ball) {
    ball->x += ball->dx;
    ball->y += ball->dy;
    ball->dx += grav[0];
    ball->dy -= grav[1];
    if (ball->x > W + ball->r) {
        ball->x = W + ball->r;
        ball->dx *= -1;
    } else if (ball->x < ball->r) {
        ball->x = ball->r;
        ball->dx *= -1;
    }
    if (ball->y > H - ball->r) {
        ball->y = H - ball->r;
        ball->dy *= -bounce;
    } else if (ball->y < ball->r) {
        ball->y = ball->r + 1;
        ball->dy *= -bounce;
    }
}

void checkCollision(Ball* ballA, Ball* ballB, int* collision, Fract* depth) {

    Fract rSum = ballA->r + ballB->r;
    Fract dx = ballB->x - ballA->x;
    Fract dy = ballB->y - ballA->y;
    *collision = (rSum * rSum > dx * dx + dy * dy);
    *depth = rSum - sqrt((dx * dx + dy * dy).getInteger());
}

void resolveCollision(Ball* ballA, Ball* ballB) {
    Fract relVel[2] = {ballB->dx - ballA->dx, ballB->dy - ballA->dy};
    Fract norm[2] = {ballB->x - ballA->x, ballB->y - ballA->y};
    Fract mag = sqrt(static_cast<float>(norm[0] * norm[0] + norm[1] * norm[1]));
    norm[0] /= mag;
    norm[1] /= mag;

    Fract velAlongNorm = relVel[0] * norm[0] + relVel[1] * norm[1];
    if (velAlongNorm > 0)
        return;

    Fract j = -(1 + bounce) * velAlongNorm;
    j /= 1 / ballA->r + 1 / ballB->r;

    Fract impulse[2] = {j * norm[0], j * norm[1]};
    ballA->dx -= 1 / ballA->r * impulse[0];
    ballA->dy -= 1 / ballA->r * impulse[1];
    ballB->dx += 1 / ballB->r * impulse[0];
    ballB->dy += 1 / ballB->r * impulse[1];

}

void adjustPositions(Ball* ballA, Ball* ballB, Fract depth) {
    const Fract percent = 0.2;
    const Fract slop = 0.01;
    Fract correction = (fmax(static_cast<float>(depth - slop), 0) / (1 / ballA->r + 1 / ballB->r)) * percent;

    Fract norm[2] = {ballB->x - ballA->x, ballB->y - ballA->y};
    Fract mag = sqrt(static_cast<float>(norm[0] * norm[0] + norm[1] * norm[1]));
    norm[0] /= mag;
    norm[1] /= mag;

    Fract cor[2];
	cor[0] = correction*norm[0];
	cor[1] = correction*norm[1];
	ballA->x -= 1/ballA->r * cor[0];
	ballA->y -= 1/ballA->r * cor[1];
	ballB->x += 1/ballB->r * cor[0];
}




void updateBalls() {

    for (int i = 0; i < numBalls; i++) {
        update(&balls[i]);
        for (int j = 0; j < i; j++) {
            if (i != j) {
                int collision;
                Fract depth;
                checkCollision(&balls[i], &balls[j], &collision, &depth);
                if (collision) {
                    adjustPositions(&balls[i], &balls[j], depth);
                    resolveCollision(&balls[i], &balls[j]);
                }
            }
        }
    }

    // Draw balls
    for (int i = 0; i < numBalls; i++) {
        Ball *ball = &balls[i];
        drawMaskedSprite(static_cast<float>(ball->x - ballRad[ball->r.getInteger()]), static_cast<float>(ball->y - ballRad[ball->r.getInteger()]), spriteFrameData[ball->frameNumber], spritePalData[ball->frameNumber],spriteMaskData[ball->frameNumber], 8);
    }

}


