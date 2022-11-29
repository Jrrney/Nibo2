/**
 * @brief Your main class
 * @author
 * @version
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h> // used for random

#include "main.h"
#include "detector.h"
#include "communicator.h"
#include "move.h"
#include "generator.h"

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
	display_init();

	gfx_init();

	// Distanzmessung anschalten
	copro_ir_startMeasure();

	// initialize xBee Module
	xBee_init();

	delay(2000);
}

/**
 * Main Method of the program.
 */
int main() {

	init();

	t_role role = detectAndSetRole();

	delay(15000);

	if (role == CAT) {
		// TODO maybe 00000000 empf
		while (true) {
			t_movement move = readMovement();
			executeMovement(move);



			// TODO stop when 00000000
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

		// TODO stop send 00000000
	}

}

