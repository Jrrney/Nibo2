#include "main.h"
#include "communicator.h"
#include "move.h"

#define CHAR_BIT 8
const unsigned int multiplicator = 10;

uint8_t read() {
	while (1) {
		if (xBee_receivedData()) {
			return xBee_readByte();
		}

		// Delay for the operation loop
		_delay_ms(5);

	}
}

void send(uint8_t data) {
	while (1) {
		if (xBee_readyToSend()) {
			xBee_sendByte(data);
		}

		// Delay for the operation loop
		_delay_ms(5);

	}
}

char *charToBinary(unsigned char c)
{
    static char bin[CHAR_BIT + 1] = {0};
    int i;

    for (i = CHAR_BIT - 1; i >= 0; i--)
    {
        bin[i] = (c % 2) + '0';
        c /= 2;
    }

    return bin;
}

void convert2BinaryString(char *str, unsigned int number, unsigned int length)
{
    unsigned int decimal = number;
    for (int i = 0; i < length; i++)
    {
        int digit = (decimal % 2);
        str[length - i - 1] = (digit == 1 ? '1' : '0');
        decimal /= 2;
    }
    printf("%s\n", str);
}

unsigned int convert2Decimal(char *str, unsigned int length)
{
    unsigned int decimal = 0;
    for (int i = 0; i < length; i++)
    {
        int digit = pow(2, i) * (str[length - i - 1] == '1' ? 1 : 0);
        decimal += digit;
    }
    return decimal;
}

t_movement decode(uint8_t data) {
	char *binaryData = charToBinary(data);

	t_movement movement;

	char *direction = malloc(2);
	strncpy(direction, binaryData + 0, 2);
	movement.direction = convert2Decimal(direction, 2);
	free(direction);

	char *ticks = malloc(3);
	strncpy(ticks, binaryData + 2, 3);
	movement.ticks = convert2Decimal(ticks, 3) * multiplicator;
	free(ticks);

	char *speed = malloc(3);
	strncpy(speed, binaryData + 5, 3);
	movement.speed = convert2Decimal(speed, 3) * multiplicator;
	free(speed);

	return movement;
}

u8_t encode(t_movement data) {
	char *res = malloc(8);

	char *dirStr = malloc(2);
	convert2BinaryString(dirStr, data.direction, 2);
	strcat(res, dirStr);
	free(dirStr);

	char *ticksStr = malloc(3);
	convert2BinaryString(ticksStr, data.ticks / multiplicator, 3);
	strcat(res, ticksStr);
	free(ticksStr);

	char *speedStr = malloc(3);
	convert2BinaryString(speedStr, data.speed / multiplicator, 3);
	strcat(res, speedStr);
	free(speedStr);

	unsigned char c = strtol(res, 0, 2);
	free(res);

	return c;
}

t_movement readMovement() {
	uint8_t res = read();
	t_movement movement = decode(res);
	return movement;
}

void sendMovement(t_movement move) {
	send(encode(move));
}
