/**
 * @author Valentin Schroeter
 * @version 1.0
 * @date 09.2019
 * @brief Methods to send and receive messages
 *  The Xbee module receives the incoming data on the UART0-Port (This is where the XBEE-Module is connected to on your Nibo)
 *        Works with 9600 bit/s with 8N1 (see e.g. http://universal_lexikon.deacademic.com/201427/8N1) !
 */

#include <avr/io.h>
#include "xBee.h"
//#include <nibo/uart0.h>
//#include <nibo/uart0.h>


/**
 * Function which initialize the UART0 Port of the Nibo and sets the baudrate of the port
 * Default baude rate of the modules is 9600
 */
void initUART0(){
    uart0_set_baudrate(9600);
    uart0_enable();
}

/**
 * Initializes and enables the xBee Module
 */
void xBee_init() {

    //LED ausschalten
    DDRE &= ~(1 << 0);

    initUART0();

}

/**
 * Transmits a single byte
 */
void xBee_sendByte(uint8_t data) {
    // -> puts the char into the buffer to send the char
    uart0_putchar(data);
}

/**
 * Checks if xBee is ready to transmit data
 */
uint8_t xBee_readyToSend() {
    return !uart0_txfull();
}

/**
 * Checks if xBee received something
 */
uint8_t xBee_receivedData() {
    return !uart0_rxempty();
}

/**
 * Reads the next byte of received data
 */
uint8_t xBee_readByte() {
    // -> get char out of the buffer
    return uart0_getchar();
}

