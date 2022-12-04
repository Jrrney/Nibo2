/**
 * @brief Your main class
 * @author
 * @version
 */
#include "main.h"

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
	display_init(DISPLAY_TYPE_TEXT);

	gfx_init();

	setDisplayPixelArt(false);

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

		evaluateNextStep();

		delay(100);

	}

}

