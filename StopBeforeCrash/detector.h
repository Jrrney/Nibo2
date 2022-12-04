#ifndef DETECT_H_
#define DETECT_H_

#include "main.h"

#define MINIMUM_DISTANCE_RIGHT 220
#define MINIMUM_DISTANCE_FRONT_RIGHT 150
#define MINIMUM_DISTANCE_FRONT 190
#define MINIMUM_DISTANCE_FRONT_LEFT 160
#define MINIMUM_DISTANCE_LEFT 220

typedef enum Sensor {
	RIGHT, FRONT_RIGHT, FRONT, FRONT_LEFT, LEFT
} t_sensor;

int getCurrentDistance(t_sensor sensor);

bool isNearSomething(t_sensor);

t_sensor detectPathOfMinResistance();

#endif
