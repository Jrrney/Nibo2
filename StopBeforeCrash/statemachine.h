#ifndef STATEM_H_
#define STATEM_H_

#include "main.h"

#define SPEED 10
#define TURNING_SPEED 5
#define TURNING_STUCK_SPEED 20

typedef enum State {
	DRIVING, TURNING_RIGHT, TURNING_LEFT, BACK_DRIVING
} t_state;

void changeState(t_state oldState, t_state newState);

void evaluateNextStep();

void setDisplayPixelArt(bool stuck);

#endif
