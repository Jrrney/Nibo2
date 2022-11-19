#ifndef COM_H_
#define COM_H_

#include "move.h"

uint8_t read();
void send(uint8_t);
t_movement readMovement();
void sendMovement(t_movement);

#endif
