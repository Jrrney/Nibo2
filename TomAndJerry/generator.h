/**
 * @file generator.h
 * @author Felix Heilmann
 * @date 19.11.2022
 * @brief Generator for random movements
 */

#include "move.h"

#ifndef GEN_H_
#define GEN_H_

#define MAX_MOVES 8
#define MIN_MOVES 3

/**
 * Generate a randomized movement.
 *
 * @return a random generated movement
 */
t_movement generateMove();

/**
 * Generates randomly generated movements.
 *
 * @return a list of random generated movements with a random size in range 3 - 8
 */
t_movement * generateMoveList();

/**
 * Generates a randomly chosen direction
 *
 * @return random direction of type t_direction
 */
t_direction getRandomDirection();

/**
 * Generates a random int in given range
 *
 * @param lower the lower interval limit
 * @param upper the upper interval limit
 *
 * @returns a random int in the given range
 */
int randomInRange(int lower, int upper);

#endif
