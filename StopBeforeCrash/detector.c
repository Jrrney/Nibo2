#include "main.h"

int getCurrentDistance(t_sensor sensor) {
	return copro_distance[sensor] / 256;
}

bool isNearSomething(t_sensor sensor) {
	bool isNearSomething = false;

	switch (sensor) {
	case RIGHT:
		isNearSomething = getCurrentDistance(RIGHT) >= MINIMUM_DISTANCE_RIGHT;
		break;
	case FRONT:
		isNearSomething |= getCurrentDistance(FRONT_RIGHT)
				>= MINIMUM_DISTANCE_FRONT_RIGHT;
		isNearSomething |= getCurrentDistance(FRONT) >= MINIMUM_DISTANCE_FRONT;
		isNearSomething |= getCurrentDistance(FRONT_LEFT)
				>= MINIMUM_DISTANCE_FRONT_LEFT;
		break;
	case FRONT_LEFT:
		isNearSomething = getCurrentDistance(FRONT_LEFT)
				>= MINIMUM_DISTANCE_FRONT_LEFT;
		break;
	case FRONT_RIGHT:
		isNearSomething = getCurrentDistance(FRONT_RIGHT)
				>= MINIMUM_DISTANCE_FRONT_RIGHT;
		break;
	case LEFT:
		isNearSomething = getCurrentDistance(LEFT) >= MINIMUM_DISTANCE_LEFT;
		break;
	default:
		break;
	}

	return isNearSomething;
}

t_sensor detectPathOfMinResistance() {
	t_sensor pathOfMinResistance = LEFT;

	int distLeft = getCurrentDistance(LEFT);
	int distFrontLeft = getCurrentDistance(FRONT_LEFT);
	int distRight = getCurrentDistance(RIGHT);
	int distFrontRight = getCurrentDistance(FRONT_RIGHT);

	if ((distLeft + distFrontLeft) > (distRight + distFrontRight)) {
		pathOfMinResistance = RIGHT;
	}

	return pathOfMinResistance;
}
