/**
 * @file move.h
 * @author Felix Heilmann
 * @date 19.11.2022
 * @brief Header File movement
 */

#ifndef MOVE_H_
#define MOVE_H_

/**
 * Enum type definition of all 4 driving directions
 */
typedef enum direction {
	FORWARD, BACKWARD, LEFT, RIGHT,
	/**
	 * Amount of all directions
	 */
	COUNT
} t_direction;

/**
 * Struct type definition of a movement
 */
typedef struct Movement {
	t_direction direction;
	// distance in ticks
	unsigned int ticks;
	// speed in ticks per second
	unsigned int speed;
} t_movement;

/**
 * Executes the given movement
 *
 * @param movement to be executed
 */
void executeMovement(t_movement movement);

#endif
