/**
 * @brief Beispiel für main.h, die man überall einbinden kann. Enthält grundlegende Typedefs, globale Makros und alle Includes, die man für den Nibo2 braucht.
 *
 * @author Valentin Schröter
 * @version 09.2019
 */

#ifndef MAIN_H_
#define MAIN_H_


//////////////////////////////////////////////////////////////////////////////////////
// ---  GLOBAL DEFINES --- ///////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

/**
 * Platz für globale Defines / Makros
 */

#define DEBUG 1


//////////////////////////////////////////////////////////////////////////////////////
// ---  INCLUDES --- /////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

// Standard Includes fuer das Funktionieren des Nibo2
#include <nibo/niboconfig.h>
#include <nibo/iodefs.h>
#include <nibo/bot.h>

// Bibliothek fuer das Ansteuern der Status LEDs
#include <nibo/leds.h>

// Bibliothek fuer Pulsweitenmodulation (PWM)
#include <nibo/pwm.h>

// Bibliothek zum Ansteuern des Display
#include <nibo/display.h>

// Bibliothek mit Grafikfunktionen
#include <nibo/gfx.h>

// Wartefunktionen
#include <nibo/delay.h>

// Coprozessorfunktionen für Motoren und Infrarot-Distanzsensoren
#include <nibo/copro.h>

// Kommunikationsfunktionen fuer die SPI Schnittstelle zum Coprozessor
#include <nibo/spi.h>

// I**2C interface, wird für NDS3 benötigt
#include <nibo/i2cmaster.h>

// NDS3 library
#include <nibo/nds3.h>

// Bibliothek fuer Bodensensoren
#include <nibo/floor.h>

// Interrupts fuer die Kommunikation mit dem Coprozessor, für PWM etc.
#include <avr/interrupt.h>

// Ein- und Ausgabefunktionen
#include <stdio.h>



//////////////////////////////////////////////////////////////////////////////////////
// ---  Typedefs --- /////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

typedef unsigned char   u8_t;
typedef signed char     i8_t;
typedef unsigned int    u16_t;
typedef signed int      i16_t;
typedef unsigned long   u32_t;
typedef signed long     i32_t;
typedef float           f32_t;




#endif  /* MAIN_H_ */
