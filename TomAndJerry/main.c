/**
 * @brief Your main class
 * @author
 * @version
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h> // used for random

#include "main.h"

typedef enum direction {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	COUNT
} t_direction;

char randomDirection() {
	char directionCode;
	// test rand() !!!
	// t_direction d = rand();

}

char generateManoveurByte(int minDistance,
								int maxDistance,
								int minSpeed,
								int maxSpeed) {
	char manoveurByte = "10101010"
	manoveurByte = randomDirection();
	manoveurByte = manoveurByte + randomDistance(minDistance, maxDistance);
	manoveurByte = manoveurByte + randomSpeed(minSpeed, maxSpeed);

	return manoveurByte;
}

/**
 * Main Method of the program.
 */
int main() {

	// using system time for setting a seed for pseudo-random number generation
	srand(time(0));

	rand()

}

