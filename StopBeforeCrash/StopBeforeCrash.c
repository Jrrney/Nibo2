/**
 * @brief Your main class
 * @author
 * @version
 */

#include "main.h"
#include <stdbool.h>

typedef enum State {
	DRIVING, TURNING_RIGHT, TURNING_LEFT, BACK_DRIVING
} state_t;

typedef enum Sensor {
	RIGHT, FRONT_RIGHT, FRONT, FRONT_LEFT, LEFT
} sensor_t;

const int MINIMUM_DISTANCE_RIGHT = 200;
const int MINIMUM_DISTANCE_RIGHT_FRONT = 200;

const int MINIMUM_DISTANCE_FRONT_RIGHT = 135;
const int MINIMUM_DISTANCE_FRONT = 200;
const int MINIMUM_DISTANCE_FRONT_LEFT = 110;

const int MINIMUM_DISTANCE_LEFT = 200;
const int MINIMUM_DISTANCE_LEFT_FRONT = 160;

const int SPEED = 10;
const int TURNING_SPEED = 5;

state_t lastState = DRIVING;
state_t currentState = DRIVING;

int getCurrentDistance(sensor_t sensor) {
	return copro_distance[sensor] / 256;
}

bool isNearSomething(sensor_t sensor) {
	bool isNearSomething = false;

	switch (sensor) {
	case RIGHT:
		isNearSomething = getCurrentDistance(RIGHT) >= MINIMUM_DISTANCE_RIGHT;
		isNearSomething |= getCurrentDistance(FRONT_RIGHT)
				>= MINIMUM_DISTANCE_FRONT_RIGHT;
		break;
	case FRONT:
		isNearSomething = getCurrentDistance(FRONT_RIGHT)
				>= MINIMUM_DISTANCE_FRONT_RIGHT;
		isNearSomething |= getCurrentDistance(FRONT) >= MINIMUM_DISTANCE_FRONT;
		isNearSomething |= getCurrentDistance(FRONT_LEFT)
				>= MINIMUM_DISTANCE_FRONT_LEFT;
		break;
	case LEFT:
		isNearSomething = getCurrentDistance(LEFT) >= MINIMUM_DISTANCE_LEFT;
		isNearSomething |= getCurrentDistance(FRONT_LEFT)
				>= MINIMUM_DISTANCE_FRONT_LEFT;
		break;
	default:
		break;
	}

	return isNearSomething;
}

void changeState(state_t oldState, state_t newState) {
	lastState = oldState;
	currentState = newState;
	switch (newState) {
	case DRIVING:
		leds_set_status(LEDS_GREEN, 4);
		leds_set_status(LEDS_GREEN, 5);
		break;
	case BACK_DRIVING:
		leds_set_status(LEDS_RED, 0);
		leds_set_status(LEDS_RED, 1);
		break;
	case TURNING_LEFT:
		leds_set_status(LEDS_ORANGE, 2);
		leds_set_status(LEDS_ORANGE, 3);
		break;
	case TURNING_RIGHT:
		leds_set_status(LEDS_ORANGE, 6);
		leds_set_status(LEDS_ORANGE, 7);
		break;
	default:
		break;
	}
}

state_t detectPathOfMinResistance() {
	state_t pathOfMinResistance = TURNING_LEFT;
	int distLeft = getCurrentDistance(LEFT);
	int distRight = getCurrentDistance(RIGHT);
	if (distLeft > distRight && distRight <= MINIMUM_DISTANCE_RIGHT) {
		pathOfMinResistance = TURNING_RIGHT;
	}
	return pathOfMinResistance;
}

void evaluateNextStep() {
	switch (currentState) {
	case DRIVING:
		if (isNearSomething(FRONT)) {
			if (isNearSomething(LEFT) && isNearSomething(RIGHT)) {
				changeState(DRIVING, BACK_DRIVING);
			} else {
				changeState(DRIVING, detectPathOfMinResistance());
			}
		} else {
			copro_setSpeed(SPEED, SPEED);
		}
		break;
	case TURNING_LEFT:
		if (!isNearSomething(LEFT)) {
			if (lastState == DRIVING) {
				if (isNearSomething(FRONT)) {
					copro_setTargetRel(-TURNING_SPEED, TURNING_SPEED, SPEED);
				} else {
					changeState(TURNING_LEFT, lastState);
				}
			} else {
				// lastState == BACK_DRIVING && left is nothing
				if (!isNearSomething(RIGHT)) {
					changeState(TURNING_LEFT, DRIVING);
				} else {
					copro_setTargetRel(-TURNING_SPEED, TURNING_SPEED, SPEED);
				}
			}
		} else {
			changeState(TURNING_LEFT, lastState);
		}
		break;
	case TURNING_RIGHT:
		if (!isNearSomething(RIGHT)) {
			if (lastState == DRIVING) {
				if (isNearSomething(FRONT)) {
					copro_setTargetRel(TURNING_SPEED, -TURNING_SPEED, SPEED);
				} else {
					changeState(TURNING_RIGHT, lastState);
				}
			} else {
				// lastState == BACK_DRIVING && right is nothing
				if (!isNearSomething(LEFT)) {
					changeState(TURNING_RIGHT, DRIVING);
				} else {
					copro_setTargetRel(TURNING_SPEED, -TURNING_SPEED, SPEED);
				}
			}
		} else {
			changeState(TURNING_RIGHT, lastState);
		}
		break;
	case BACK_DRIVING:
		if (!isNearSomething(LEFT) || !isNearSomething(RIGHT)) {
			changeState(BACK_DRIVING, detectPathOfMinResistance());
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

	// initialisiert das Display und die Grafikfunktionen
	display_init();
	gfx_init();

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

		printDistances();

		evaluateNextStep();

		delay(100);

	}

}

