/**
 * @brief Your main class
 * @author
 * @version
 */
#include "main.h"
#include <stdbool.h>

//#ifndef display_init
//#define display_init() display_init(DISPLAY_TYPE_TEXT);
//#endif

// Die darzustellende Grafik
#include "good.xbm"
#include "bad.xbm"

typedef enum State {
	DRIVING, TURNING_RIGHT, TURNING_LEFT, BACK_DRIVING, STUCK, NOT_STUCK
} state_t;

typedef enum Sensor {
	RIGHT, FRONT_RIGHT, FRONT, FRONT_LEFT, LEFT
} sensor_t;

const int MINIMUM_DISTANCE_RIGHT = 220;
const int MINIMUM_DISTANCE_RIGHT_FRONT = 120;

const int MINIMUM_DISTANCE_FRONT_RIGHT = 150;
const int MINIMUM_DISTANCE_FRONT = 190;
const int MINIMUM_DISTANCE_FRONT_LEFT = 160;

const int MINIMUM_DISTANCE_LEFT = 220;
const int MINIMUM_DISTANCE_LEFT_FRONT = 160;

const int SPEED = 10;
const int TURNING_SPEED = 5;
const int TURNING_STUCK_SPEED = 20;

state_t lastState = DRIVING;
state_t currentState = DRIVING;
state_t currentStuckState = NOT_STUCK;

int getCurrentDistance(sensor_t sensor) {
	return copro_distance[sensor] / 256;
}

bool isNearSomething(sensor_t sensor) {
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

/**
 * @param oldState the state
 * @param newState
 */
void changeState(state_t oldState, state_t newState) {
	lastState = oldState;
	currentState = newState;
	switch (newState) {
	case DRIVING:
		leds_set_status(LEDS_OFF, 0);
		leds_set_status(LEDS_OFF, 1);
		leds_set_status(LEDS_OFF, 2);
		leds_set_status(LEDS_OFF, 3);
		leds_set_status(LEDS_GREEN, 4);
		leds_set_status(LEDS_GREEN, 5);
		leds_set_status(LEDS_OFF, 6);
		leds_set_status(LEDS_OFF, 7);
		break;
	case BACK_DRIVING:
		leds_set_status(LEDS_RED, 0);
		leds_set_status(LEDS_RED, 1);
		leds_set_status(LEDS_OFF, 2);
		leds_set_status(LEDS_OFF, 3);
		leds_set_status(LEDS_OFF, 4);
		leds_set_status(LEDS_OFF, 5);
		leds_set_status(LEDS_OFF, 6);
		leds_set_status(LEDS_OFF, 7);
		break;
	case TURNING_LEFT:
		leds_set_status(LEDS_OFF, 0);
		leds_set_status(LEDS_OFF, 1);
		leds_set_status(LEDS_ORANGE, 2);
		leds_set_status(LEDS_ORANGE, 3);
		leds_set_status(LEDS_OFF, 4);
		leds_set_status(LEDS_OFF, 5);
		leds_set_status(LEDS_OFF, 6);
		leds_set_status(LEDS_OFF, 7);
		break;
	case TURNING_RIGHT:
		leds_set_status(LEDS_OFF, 0);
		leds_set_status(LEDS_OFF, 1);
		leds_set_status(LEDS_OFF, 2);
		leds_set_status(LEDS_OFF, 3);
		leds_set_status(LEDS_OFF, 4);
		leds_set_status(LEDS_OFF, 5);
		leds_set_status(LEDS_ORANGE, 6);
		leds_set_status(LEDS_ORANGE, 7);
		break;
	default:
		break;
	}
}

void changeStuckState(state_t newState) {
	if (newState == currentStuckState)
		return;
	currentStuckState = newState;

	//reinige Display
	gfx_move(0, 0);
	gfx_fill(0);

	if (newState == STUCK) {
		gfx_draw_xbm_P(bad_width, bad_height, (PGM_P) bad_bits);
	} else {
		gfx_draw_xbm_P(good_width, good_height, (PGM_P) good_bits);
	}
}

state_t detectPathOfMinResistance() {
	state_t pathOfMinResistance = TURNING_LEFT;
	int distLeft = getCurrentDistance(LEFT);
	int distFrontLeft = getCurrentDistance(FRONT_LEFT);
	int distRight = getCurrentDistance(RIGHT);
	int distFrontRight = getCurrentDistance(FRONT_RIGHT);
	if ((distLeft + distFrontLeft) > (distRight + distFrontRight)) {
		pathOfMinResistance = TURNING_RIGHT;
	}
	return pathOfMinResistance;
}

void evaluateNextStep() {
	switch (currentState) {
	case DRIVING:
		if (isNearSomething(FRONT)) {
			changeStuckState(STUCK);
//			if (isNearSomething(LEFT) && isNearSomething(RIGHT)) {
//				changeState(DRIVING, BACK_DRIVING);
//			} else {
//				changeState(DRIVING, detectPathOfMinResistance());
//			}
			if (isNearSomething(LEFT) && isNearSomething(RIGHT)
					&& isNearSomething(FRONT)) {
				changeState(DRIVING, BACK_DRIVING);
			} else {
				changeState(DRIVING, detectPathOfMinResistance());
			}
		} else {
			changeStuckState(NOT_STUCK);
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
			// lastState == BACK_DRIVING && left is nothing
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
			// lastState == BACK_DRIVING && left is nothing
			copro_setTargetRel(TURNING_STUCK_SPEED, -TURNING_STUCK_SPEED,
					SPEED);
			delay(2500);
			changeState(TURNING_RIGHT, BACK_DRIVING);
		}
		break;
	case BACK_DRIVING:
		if (lastState != DRIVING && !isNearSomething(FRONT)) {
			changeState(BACK_DRIVING, DRIVING);
		} else if (getCurrentDistance(FRONT_LEFT) <= 130
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

void printDistances() {
	char output[20] = "";

	// Display leeren
	gfx_fill(0);

	// Beschreibung
	gfx_move(0, 0);
	gfx_print_text("Distanzen");

	for (int i = 0; i < 5; i++) {
		// Ausgabe
		sprintf(output, "%3i", (copro_distance[i] / 256));
		gfx_move(23 * i, 10);
		gfx_print_text(output);
	}
	sprintf(output, "%3i", currentState);
	gfx_move(0, 30);
	gfx_print_text(output);

}
/**
 * inits all components
 */
void init() {
	// Aktivierung von Interrupts
	sei();

	// Initialisierung des Roboters (immer noetig)
	bot_init();

	// Initialisierung der SPI Schnittstelle
	spi_init();

	// Initialisierung der LEDs
	leds_init();

	changeState(DRIVING, DRIVING);

	changeStuckState(NOT_STUCK);

	// initialisiert das Display und die Grafikfunktionen
	display_init();

	gfx_init();

	gfx_move(0, 0);
	gfx_fill(0);
	gfx_draw_xbm_P(good_width, good_height, (PGM_P) good_bits);

	// Distanzmessung anschalten
	copro_ir_startMeasure();
}

/**
 * Main Method of the program.
 */
int main() {
	init();

	while (1) {

		// Aktualisierung aller Daten vom Coprozessor
		copro_update();

//		printDistances();

		evaluateNextStep();

		delay(100);

	}

}

