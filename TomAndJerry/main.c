/**
 * @file main.c
 * @brief main logic
 * @author Jenny Dietrich
 * @version 19.11.2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h> // used for random

#include "main.h"
#include "detector.h"
#include "communicator.h"
#include "move.h"
#include "generator.h"

/**
 * Initializing all used NIBO components
 */
void init() {
	// using system time for setting a seed for pseudo-random number generation
	srand(time(0));

	// Aktivierung von Interrupts
	sei();

	// Initialisierung des Roboters (immer noetig)
	bot_init();

	// Initialisierung der SPI Schnittstelle
	spi_init();

	// Initialisierung der LEDs
	leds_init();

	// initialisiert das Display und die Grafikfunktionen
	display_init(DISPLAY_TYPE_TEXT);

	gfx_init();

	// Distanzmessung anschalten
	copro_ir_startMeasure();

	// initialize xBee Module
	xBee_init();

	delay(2000);
}

/**
 * Main logic, detects role and executes to role related code
 */
int main() {

	init();

	t_role role = detectAndSetRole();

	delay(15000);

	if (role == CAT) {
		while (true) {
			t_movement move = readMovement();
			if (move.direction == 0 && move.ticks == 0 && move.speed == 0) {
				break;
			}
			executeMovement(move);
		}
	} else if (role == MOUSE) {

		int length = randomInRange(5, 8);
		t_movement *movements = generateMoveList(length);

		for (int moveIndex = 0; moveIndex < length; moveIndex++) {
			t_movement move = movements[moveIndex];
			sendMovement(move);
			executeMovement(move);

			delay(2000);

		}

		send(0);
	}

	resetRole();

}

