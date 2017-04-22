/*
 * system.h
 *
 *  Created on: Feb 7, 2015
 *      Author: Anthony
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_
// CC3200: 		80000000
// MSP430F5529	2^15*32 = 1048576
#define FCPU 25000000
#define PERIPHERAL_CLOCK FCPU

// include the library header
#include "library.h"
// let the system know which lower level modules are in use
// this way higher modules can selectively utilize their resources
#define USE_MODULE_TASK
#define USE_MODULE_TIMING
#define USE_MODULE_LIST
#define USE_MODULE_BUFFER
#define USE_MODULE_SUBSYS
#define USE_MODULE_BUFFER_PRINTF
#define USE_MODULE_UART

#define GAME_CONTROLLER_UART 0
#define SUBSYS_UART 1

#define USE_UPACKET_0
#define USE_UPACKET_1 // We will need two instances of UART packet to allow daisy-chaining controllers
#define USE_UART0
#define USE_UART1

#define MAX_TASK_LENGTH 40

//#define UART0_TX_GPIO 1
//#define UART0_RX_GPIO 2
//#define UART1_TX_GPIO 1
//#define UART1_RX_GPIO 2
/** You must define system-related parameters such as FCPU in your system.h file
*  All constants defined here are specific to use of the controller module client
*  You also MUST define two UART channels CMC_UART_UPSTREAM and CMC_UART_DOWNSTREAM
*  for this module to use with your microcontroller (Ex: MSP430 has UART0 and UART1)
*/

// Move to system.h later, these are the UART interfaces specified by the embedded library that we must use
#define CMC_UART_UPSTREAM 1 // Use UART0 for upstream communication
#define CMC_UART_DOWNSTREAM 0 // Use UART1 for downstream communication

#define UART_BAUD 115200	// Run the system at this baud rate

//#define SUBSYS_UART UART1

#endif /* SYSTEM_H_ */
