#include "main.h"

#include "good.xbm"
#include "bad.xbm"

t_state lastState = DRIVING;
t_state currentState = DRIVING;

/**
 * @param oldState the state
 * @param newState
 */
void changeState(t_state oldState, t_state newState) {
	lastState = oldState;
	currentState = newState;

	leds_set_status(LEDS_OFF, 0);
	leds_set_status(LEDS_OFF, 1);
	leds_set_status(LEDS_OFF, 2);
	leds_set_status(LEDS_OFF, 3);
	leds_set_status(LEDS_OFF, 4);
	leds_set_status(LEDS_OFF, 5);
	leds_set_status(LEDS_OFF, 6);
	leds_set_status(LEDS_OFF, 7);

	switch (newState) {
	case DRIVING:
		leds_set_status(LEDS_GREEN, 4);
		leds_set_status(LEDS_GREEN, 5);
		setDisplayPixelArt(false);
		break;
	case BACK_DRIVING:
		leds_set_status(LEDS_RED, 0);
		leds_set_status(LEDS_RED, 1);
		setDisplayPixelArt(true);
		break;
	case TURNING_LEFT:
		leds_set_status(LEDS_ORANGE, 2);
		leds_set_status(LEDS_ORANGE, 3);
		setDisplayPixelArt(true);
		break;
	case TURNING_RIGHT:
		leds_set_status(LEDS_ORANGE, 6);
		leds_set_status(LEDS_ORANGE, 7);
		setDisplayPixelArt(true);
		break;
	default:
		break;
	}
}

void evaluateNextStep() {
	switch (currentState) {
	case DRIVING:
		if (isNearSomething(FRONT)) {
			if (isNearSomething(LEFT) && isNearSomething(RIGHT)
					&& isNearSomething(FRONT) && isNearSomething(FRONT_LEFT) && isNearSomething(FRONT_RIGHT)) {
				changeState(DRIVING, BACK_DRIVING);
			} else {
				t_sensor sensor = detectPathOfMinResistance();
				if(sensor == LEFT) {
					changeState(DRIVING, TURNING_LEFT);
				} else if(sensor == RIGHT) {
					changeState(DRIVING, TURNING_RIGHT);
				}
			}
		} else {
			copro_setSpeed(SPEED, SPEED);
		}
		break;
	case TURNING_LEFT:
		if (lastState == DRIVING) {
			if (isNearSomething(FRONT)) {
				copro_setTargetRel(-TURNING_SPEED, TURNING_SPEED, SPEED);
			} else {
				changeState(TURNING_LEFT, lastState);
			}
		} else {
			copro_setTargetRel(-TURNING_STUCK_SPEED, TURNING_STUCK_SPEED,
					SPEED);
			delay(2500);
			changeState(TURNING_LEFT, BACK_DRIVING);
		}
		break;
	case TURNING_RIGHT:
		if (lastState == DRIVING) {
			if (isNearSomething(FRONT)) {
				copro_setTargetRel(TURNING_SPEED, -TURNING_SPEED, SPEED);
			} else {
				changeState(TURNING_RIGHT, DRIVING);
			}
		} else {
			copro_setTargetRel(TURNING_STUCK_SPEED, -TURNING_STUCK_SPEED,
					SPEED);
			delay(2500);
			changeState(TURNING_RIGHT, BACK_DRIVING);
		}
		break;
	case BACK_DRIVING:
		if (getCurrentDistance(FRONT_LEFT) <= 130
				&& getCurrentDistance(LEFT) <= 40) {
			changeState(BACK_DRIVING, TURNING_LEFT);
		} else if (getCurrentDistance(FRONT_RIGHT) <= 100
				&& getCurrentDistance(RIGHT) <= 40) {
			changeState(BACK_DRIVING, TURNING_RIGHT);
		} else {
			copro_setSpeed(-SPEED, -SPEED);
		}
		break;
	default:
		break;
	}
}

void setDisplayPixelArt(bool stuck) {
	//reinige Display
	gfx_move(0, 0);
	gfx_fill(0);

	if (stuck) {
		gfx_draw_xbm_P(bad_width, bad_height, (PGM_P) bad_bits);
	} else {
		gfx_draw_xbm_P(good_width, good_height, (PGM_P) good_bits);
	}
}
