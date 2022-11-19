/**
 * @author Valentin Schroeter
 * @version 1.0
 * @date 09.2019
 * @brief Methods to send and receive messages
 */

#ifndef NIBO_xBee_H_
#define NIBO_xBee_H_

#ifndef NIBO_USE_UART0
#define NIBO_USE_UART0
#endif

// The XBee module communicates over UART
#include <nibo/uart0.h>

#include <stdint.h>


/**
 * Initializes and enables the xBee Module
 */
void xBee_init();

/**
 * Transmits a single byte
 */
void xBee_sendByte(uint8_t data);

/**
 * Checks if xBee is ready to transmit data
 */
uint8_t xBee_readyToSend();

/**
 * Checks if xBee received something
 */
uint8_t xBee_receivedData();

/**
 * Reads the next byte of received data
 */
uint8_t xBee_readByte();


#endif // NIBO_xBee_H
