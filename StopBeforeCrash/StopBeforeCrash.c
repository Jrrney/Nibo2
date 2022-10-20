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

const int MINIMUM_DISTANCE_RIGHT = 140;
const int MINIMUM_DISTANCE_FRONT_RIGHT = 110;
const int MINIMUM_DISTANCE_FRONT = 230;
const int MINIMUM_DISTANCE_FRONT_LEFT = 100;
const int MINIMUM_DISTANCE_LEFT = 140;

const int SPEED = 10;

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
		break;
	case FRONT:
		isNearSomething = getCurrentDistance(FRONT_RIGHT)
				>= MINIMUM_DISTANCE_FRONT_RIGHT;
		isNearSomething |= getCurrentDistance(FRONT) >= MINIMUM_DISTANCE_FRONT;
		isNearSomething |= getCurrentDistance(FRONT_LEFT)
				>= MINIMUM_DISTANCE_FRONT_LEFT;
		break;
	case FRONT_LEFT:
		isNearSomething = getCurrentDistance(FRONT_LEFT)
				>= MINIMUM_DISTANCE_FRONT_LEFT;
		break;
	case LEFT:
		isNearSomething = getCurrentDistance(LEFT) >= MINIMUM_DISTANCE_LEFT;
		break;
	default:
		break;
	}

	return isNearSomething;
}

void changeState(state_t oldState, state_t newState) {
	lastState = oldState;
	currentState = newState;
}

void check() {
	switch (currentState) {
	case DRIVING:
		if (isNearSomething(FRONT)) {
			if (isNearSomething(LEFT) && isNearSomething(RIGHT)) {
				changeState(DRIVING, BACK_DRIVING);
			} else if (!isNearSomething(LEFT)) {
				changeState(DRIVING, TURNING_LEFT);
			} else if (isNearSomething(RIGHT)) {
				changeState(DRIVING, TURNING_RIGHT);
			}
		} else {
			copro_setSpeed(SPEED, SPEED);
		}
		break;
	case TURNING_LEFT:
		if (!isNearSomething(FRONT) && !isNearSomething(FRONT_LEFT)) {
			changeState(TURNING_LEFT, DRIVING);
		} else {
			copro_setTargetRel(-5, 5, SPEED);
		}
		break;
	case TURNING_RIGHT:
		if (!isNearSomething(FRONT)) {
			changeState(TURNING_RIGHT, DRIVING);
		} else {
			copro_setTargetRel(5, -5, SPEED);
		}
		break;
	case BACK_DRIVING:
		if (!isNearSomething(LEFT)) {
			changeState(BACK_DRIVING, TURNING_LEFT);
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

	int speed = 10;

	while (1) {

		// Aktualisierung aller Daten vom Coprozessor
		copro_update();

		printDistances();

		check();

		delay(100);

	}

}

