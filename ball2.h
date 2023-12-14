#define MAX_BALLS 100
#define W 104
#define H 176
#define L 49
double bounce = 0.03;				                                //	var bounce = 0.7;		

typedef struct {
    double x;
    double y;
    double dx;
    double dy;
    uint8_t r;
    char color[20];
    char frameNumber;
} Ball;

const uint8_t ballRad[] = {4,5,7,8,11,14,16,19,22,27,32};

int numBalls = 1;
double grav[2] = {0, -0.1};

Ball balls[MAX_BALLS];


void update(Ball* ball) {
    ball->x += ball->dx;		    //	this.x += this.dx;	
    ball->y += ball->dy;		    //	this.y += this.dy;	
    ball->dx += grav[0];		    //	this.dx += grav[0];	
    ball->dy -= grav[1];		    //	this.dy -= grav[1];	
    if (ball->x > L+W - ball->r) {    //	if(this.x > W - this.r) {	
        ball->x = L+W - ball->r;	    //		this.x = W - this.r;
        ball->dx *= -1; 		    //		this.dx *= -1;
    } else if (ball->x < L+ball->r) {	//	} else if(this.x < this.r) {	
        ball->x = L+ball->r;		    //		this.x = this.r;
        ball->dx *= -1;		        //		this.dx *= -1;
    }		                        //	}	
    if (ball->y > H - ball->r) {	//	if(this.y > H - this.r) {	
        ball->y = H - ball->r;		//		this.y = H - this.r;
        ball->dy *= -bounce;		    //		this.dy *= -0.7;
    } else if (ball->y < ball->r) {	//	} else if(this.y < this.r) {	
        ball->y = ball->r + 1;		//		this.y = this.r + 1;
        ball->dy *= -bounce;		    //		this.dy *= -0.7;
    }		                        //	}	
}

void checkCollision(Ball* ballA, Ball* ballB, int* collision, double* depth) {

    //	var rSum = ballA.r + ballB.r;
    //	var dx = ballB.x - ballA.x;
    //	var dy = ballB.y - ballA.y;
    //	return [rSum*rSum > dx*dx + dy*dy,rSum-Math.sqrt(dx*dx+dy*dy)];

    double rSum = ballA->r + ballB->r;
    double dx = ballB->x - ballA->x;
    double dy = ballB->y - ballA->y;
    *collision = (rSum * rSum > dx * dx + dy * dy);
    *depth = rSum - sqrt(dx * dx + dy * dy);
}

void resolveCollision(Ball* ballA, Ball* ballB) {
    double relVel[2] = {ballB->dx - ballA->dx, ballB->dy - ballA->dy};	//	var relVel = [ballB.dx - ballA.dx,ballB.dy - ballA.dy];		
    double norm[2] = {ballB->x - ballA->x, ballB->y - ballA->y};		//	var norm = [ballB.x - ballA.x, ballB.y - ballA.y];		
    double mag = sqrt(norm[0] * norm[0] + norm[1] * norm[1]);		    //	var mag = Math.sqrt(norm[0]*norm[0] + norm[1]*norm[1]);		
    norm[0] /= mag;				                                        //	norm = [norm[0]/mag,norm[1]/mag];		
    norm[1] /= mag;				                                        //			

    double velAlongNorm = relVel[0] * norm[0] + relVel[1] * norm[1];	//	var velAlongNorm = relVel[0]*norm[0] + relVel[1]*norm[1];		
    if (velAlongNorm > 0)				                                //	if(velAlongNorm > 0)		
        return;			                                                //		return;	

    double j = -(1 + bounce) * velAlongNorm;				            //	var j = -(1 + bounce) * velAlongNorm;		
    j /= 1 / ballA->r + 1 / ballB->r;   				                //	j /= 1/ballA.r + 1/ballB.r;		

    double impulse[2] = {j * norm[0], j * norm[1]};				        //	var impulse = [j*norm[0],j*norm[1]];		
    ballA->dx -= 1 / ballA->r * impulse[0];				                //	ballA.dx -= 1/ballA.r * impulse[0];		
    ballA->dy -= 1 / ballA->r * impulse[1];				                //	ballA.dy -= 1/ballA.r * impulse[1];		
    ballB->dx += 1 / ballB->r * impulse[0];				                //	ballB.dx += 1/ballB.r * impulse[0];		
    ballB->dy += 1 / ballB->r * impulse[1];				                //	ballB.dy += 1/ballB.r * impulse[1];		

}

void adjustPositions(Ball* ballA, Ball* ballB, double depth) {
    const double percent = 0.2;					                                            //	const percent = 0.2;
    const double slop = 0.01;					                                            //	const slop = 0.01;
    double correction = (fmax(depth - slop, 0) / (1 / ballA->r + 1 / ballB->r)) * percent;	//	var correction = (Math.max(depth - slop, 0) / (1/ballA.r + 1/ballB.r)) * percent;

    double norm[2] = {ballB->x - ballA->x, ballB->y - ballA->y};					        //	var norm = [ballB.x - ballA.x, ballB.y - ballA.y];
    double mag = sqrt(norm[0] * norm[0] + norm[1] * norm[1]);					            //	var mag = Math.sqrt(norm[0]*norm[0] + norm[1]*norm[1]);
    norm[0] /= mag;					                                                        //	norm = [norm[0]/mag,norm[1]/mag];
    norm[1] /= mag;					                                                        //	

    double cor[2];					                                                        //	
	cor[0] = correction*norm[0];				                                            //	correction = [correction*norm[0],correction*norm[1]];
	cor[1] = correction*norm[1];				                                            //	ballA.x -= 1/ballA.r * correction[0];
	ballA->x -= 1/ballA->r * cor[0];				                                        //	ballA.y -= 1/ballA.r * correction[1];
	ballA->y -= 1/ballA->r * cor[1];				                                        //	ballB.x += 1/ballB.r * correction[0];
	ballB->x += 1/ballB->r * cor[0];				                                        //	ballB.y += 1/ballB.r * correction[1];
}




void updateBalls() {

    // Update balls
/*
	for(var ball of balls) {
		ball.update();
		for(var ball2 of balls) { //Not the most efficient way to check every pair, but this is just a rough version
			if(ball !== ball2) {
				var collision = checkCollision(ball, ball2);
				if(collision[0]) {
					adjustPositions(ball,ball2,collision[1]);
					resolveCollision(ball,ball2);
				}
			}
		} 
	}
*/

    for (int i = 0; i < numBalls; i++) {
        update(&balls[i]);
        for (int j = 0; j < numBalls; j++) {
            if (i != j) {
                int collision;
                double depth;
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
        drawMaskedSprite((ball->x - ballRad[ball->r]), (ball->y - ballRad[ball->r]), spriteFrameData[ball->frameNumber], spritePalData[ball->frameNumber],spriteMaskData[ball->frameNumber], 8);
    }

}


