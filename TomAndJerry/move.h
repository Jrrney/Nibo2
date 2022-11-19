#ifndef MOVE_H_
#define MOVE_H_

typedef enum direction {
	FORWARD, BACKWARD, LEFT, RIGHT, COUNT
} t_direction;

typedef struct Movement {
	t_direction direction;
	unsigned int ticks;
	unsigned int speed;
} t_movement;

void executeMovement(t_movement movement);

#endif
