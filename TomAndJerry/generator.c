#include "main.h"
#include "generator.h"

unsigned int MULTIPLIER_SPEED = 7;
unsigned int MULTIPLIER_TICKS = 15;

int randomInRange(int lower, int upper) {
	int random = rand();
	int r = (random % (upper - lower + 1)) + lower;

	return r;
}

t_direction getRandomDirection() {
	return randomInRange(0, COUNT - 1);
}

t_movement generateMove() {
	t_movement move = { };

	move.direction = getRandomDirection();
	move.ticks = randomInRange(1, 7) * MULTIPLIER_TICKS;
	move.speed = randomInRange(1, 7) * MULTIPLIER_SPEED;

	return move;
}

t_movement* generateMoveList(int numberOfMoves) {
	t_movement *moveList = malloc(numberOfMoves * sizeof(t_movement));

	for (int i = 0; i < numberOfMoves; i++) {
		moveList[i] = generateMove();
	}

	return moveList;
}
