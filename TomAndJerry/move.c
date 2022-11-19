#include "main.h"
#include "move.h"

void executeMovement(t_movement movement) {
	t_direction direction = movement.direction;
	unsigned int ticks = movement.ticks;
	unsigned int speed = movement.speed;
	switch (direction) {
		case FORWARD:
			copro_setTargetRel(ticks, ticks, speed);
			break;
		case BACKWARD:
			copro_setTargetRel(-ticks, -ticks, speed);
			break;
		case LEFT:
//			copro_setTargetRel(-ticks, ticks, speed);
			copro_setTargetRel(0, ticks, speed);
			break;
		case RIGHT:
//			copro_setTargetRel(ticks, -ticks, speed);
			copro_setTargetRel(ticks, 0, speed);
			break;
		default:
			break;
	}

	delay(1000 * ticks / speed);
}

// zwischen 240 und 60 abstand vorne
int calculateFrontDistanceInCm() {
	double f = (double) (copro_distance[2]/256) - 60.0;
	double e = ((-4.0/20625.0) * f * f) + ((872.0/12375.0) * f);
	return (6.4 - e) + 5;
}
