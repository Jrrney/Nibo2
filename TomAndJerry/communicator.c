#include "communicator.h"

#define CHAR_BIT 8

unsigned int MULTIPLIER_SPEED_C = 7;
unsigned int MULTIPLIER_TICKS_C = 15;

uint8_t read() {
	while (1) {
		if (xBee_receivedData()) {
			return xBee_readByte();
		}

		// Delay for the operation loop
		_delay_ms(5);

	}
}

void send(unsigned char data) {
	while (1) {
		if (xBee_readyToSend()) {
			xBee_sendByte(data);
			return;
		}
		// Delay for the operation loop
		_delay_ms(5);

	}
}

char* charToBinary(unsigned char c) {
	static char bin[CHAR_BIT + 1] = { 0 };
	int i;

	for (i = CHAR_BIT - 1; i >= 0; i--) {
		bin[i] = (c % 2) + '0';
		c /= 2;
	}

	return bin;
}

char* toBinaryString(int n) {
	char *string = malloc(sizeof(int) * 8 + 1);
	if (!string) {
		return NULL;
	}
	for (int i = 31; i >= 0; i--) {
		string[i] = n & 1;
		n >>= 1;
	}
	return string;
}

void convert2BinaryString(char *str, unsigned int number, unsigned int length) {
	unsigned int decimal = number;
	for (int i = 0; i < length; i++) {
		str[length - i - 1] = (decimal % 2) + '0';
		decimal /= 2;
	}
}

t_movement decode(unsigned char data) {
	char *binaryData = charToBinary(data);

	t_movement movement;

	char direction[2];
	strncpy(direction, binaryData + 0, 2);
	int direction_int = strtol(direction, NULL, 2);
	movement.direction = direction_int;

	char ticks[3];
	strncpy(ticks, binaryData + 2, 3);
	int ticks_int = strtol(ticks, NULL, 2);
	movement.ticks = ticks_int * MULTIPLIER_TICKS_C;

	char speed[3];
	strncpy(speed, binaryData + 5, 3);
	int speed_int = strtol(speed, NULL, 2);
	movement.speed = speed_int * MULTIPLIER_SPEED_C;

	return movement;
}

void printMovement(t_movement move) {
	gfx_fill(0);
	char output[20] = "";

	gfx_move(0, 0);
	sprintf(output, "%3i", move.direction);
	gfx_print_text(output);
	gfx_move(0, 10);
	sprintf(output, "%3i", move.ticks);
	gfx_print_text(output);
	gfx_move(0, 20);
	sprintf(output, "%3i", move.speed);
	gfx_print_text(output);
}

unsigned char encode(t_movement data) {
	char res[8 + 1];

	char dirStr[2];
	convert2BinaryString(dirStr, data.direction, 2);
	res[0] = dirStr[0];
	res[1] = dirStr[1];

	char ticksStr[3];
	convert2BinaryString(ticksStr, data.ticks / MULTIPLIER_TICKS_C, 3);
	res[2] = ticksStr[0];
	res[3] = ticksStr[1];
	res[4] = ticksStr[2];

	char speedStr[3];
	convert2BinaryString(speedStr, data.speed / MULTIPLIER_SPEED_C, 3);
	res[5] = speedStr[0];
	res[6] = speedStr[1];
	res[7] = speedStr[2];

	unsigned char c = strtol(res, NULL, 2);

	return c;
}

t_movement readMovement() {
	t_movement r = decode(read());

	printMovement(r);

	return r;
}

void sendMovement(t_movement move) {
	unsigned char e = encode(move);

	printMovement(move);

	send(e);
}
