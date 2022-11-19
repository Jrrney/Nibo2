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

//char randomDirection() {
//	char directionCode;
// test rand() !!!
// t_direction d = rand();

//}

//char generateManoveurByte(int minDistance,
//								int maxDistance,
//								int minSpeed,
//								int maxSpeed) {
//	char manoveurByte = "10101010"
//	manoveurByte = randomDirection();
//	manoveurByte = manoveurByte + randomDistance(minDistance, maxDistance);
//	manoveurByte = manoveurByte + randomSpeed(minSpeed, maxSpeed);
//
//	return manoveurByte;
//}

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

	// initialize xBee Module
	xBee_init();
}

/**
 * Main Method of the program.
 */
int main() {

	// using system time for setting a seed for pseudo-random number generation
	srand(time(0));

	init();

	delay(1000);

//	rand()

	t_role role = detectAndSetRole();

}

