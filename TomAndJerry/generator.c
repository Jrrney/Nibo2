#include "main.h"
#include "generator.h"

t_movement generateMove() {
	t_movement move;

	move.direction = getRandomDirection();
	move.ticks = randomInRange(1, 7);
	move.speed = randomInRange(1, 7);

	return move;
}

t_movement * generateMoveList() {
	static t_movement moveList[randomInRange(MIN_MOVES, MAX_MOVES)];
	int numberOfMoves = sizeof(moveList)/sizeof(t_movement);

	for (int i = 0; i < numberOfMoves; i++) {
		moveList[i] = generateMove();
	}

	return moveList;
}

t_direction getRandomDirection() {
	t_direction rDirection = randomInRange(0, COUNT - 1);
	return rDirection;
}

int randomInRange(int lower, int upper) {
	return (rand() % (upper - lower + 1)) + lower;
}
