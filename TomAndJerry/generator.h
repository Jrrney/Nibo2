#include "move.h"
//#include

#ifndef GEN_H_
#define GEN_H_

#define MAX_MOVES 8
#define MIN_MOVES 3

/**
 * Generate a randomized movement for cat and mouse.
 */
t_movement generateMove();

/**
 * Returns a pointer to a Array of randomly generated movements.
 *
 * The number of moves to be generated is determined randomly and is between
 * MIN_MOVES and MAX_MOVES.
 */
t_movement * generateMoveList();

/**
 * Returns a randomly chosen direction of the t_direction enum.
 */
t_direction getRandomDirection();

int randomInRange(int lower, int upper);

#endif
