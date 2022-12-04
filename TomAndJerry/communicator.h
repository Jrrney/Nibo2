/**
 * @file communicator.h
 * @author Jenny Dietrich
 * @date 19.11.2022
 * @brief xbee movement transmission related functions
 */

#ifndef COM_H_
#define COM_H_

#include "move.h"
#include "main.h"

/**
 * reads from xbee module until something has arrived
 *
 * @return the 8-bit big read message
 */
uint8_t read();

/**
 * sends a 8-bit big message to the xbee module
 *
 * @param the message to be send
 */
void send(uint8_t);

/**
 * reads from xbee module until something has arrived and decodes to a movement
 *
 * @return the received decoded movement
 */
t_movement readMovement();

/**
 * encodes and sends a movement to a 8-bit message to the xbee module
 *
 * @param the movement to be send
 */
void sendMovement(t_movement);

#endif
