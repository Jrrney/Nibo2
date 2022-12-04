/**
 * @file move.c
 * @author Felix Heilmann
 * @date 19.11.2022
 * @brief movement related functions
 */

#include "main.h"
#include "move.h"

/**
 * Executes a movement
 * Turn left and right does not turn on spot, only one wheel is moving
 *
 * @param movement the movement to be executed
 */
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
			copro_setTargetRel(0, ticks, speed);
			break;
		case RIGHT:
			copro_setTargetRel(ticks, 0, speed);
			break;
		default:
			break;
	}

	// the
	delay(1000 * ticks / speed);
}

/**
 * Calculates the distance in centimeters in front of the NIBO
 * works in range 60 - 240
 */
int calculateFrontDistanceInCm() {
	double f = (double) (copro_distance[2]/256) - 60.0;
	double e = ((-4.0/20625.0) * f * f) + ((872.0/12375.0) * f);
	return (6.4 - e) + 5;
}
