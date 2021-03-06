/*
 * system.h
 *
 *  Created on: Feb 7, 2015
 *      Author: Anthony
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

#define FCPU 24000000
#define PERIPHERAL_CLOCK FCPU

#define THIS_NODE LECAKES
#define THIS_NODE2 MASTER

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
#define USE_MODULE_GAME_CONTROLLER
#define USE_SPI2
#define USE_SPI_B0
#define SPI_MAX_SIZE 33
#define SUBSYS_UART 0

#define UART1_TX_BUFFER_LENGTH 1024
#define UART0_TX_BUFFER_LENGTH 1024

#define USE_UPACKET_0
#define USE_UART0
#define USE_UART1

#define GAME_CONTROLLER_UART 1
#define USE_MODULE_GAME_NFR24

#define UART_BAUD 115200	// Run the system at this baud rate

void Game_nRF_Test_Init(void);
//#define SUBSYS_UART UART1

#endif /* SYSTEM_H_ */
