/** 
 * @defgroup hal_spi_tivactm4c123 SPI Hardware Abstraction Layer for Tiva C TM4C123
 * @ingroup hal_spi
 *
 * @author Anthony Merlino, Breanna Higgins
 *
 * Based on hal_spi.h for msp430f5529
 *
 * @{
 */
 
#ifndef _HAL_SPI_H_
#define _HAL_SPI_H_

#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/ssi.h"
#include "driverlib/sysctl.h"
#include "system.h"


 
 /**
  * @brief spi settings structure
  */
typedef struct hal_spi_settings_t {
	uint8_t bytesToSend 	: 8; 		///<Size of data
	uint8_t modeOfOperation : 1;		///<SSI Module operation mode (can be \b SSI_MODE_MASTER, \b SSI_MODE_SLAVE, or \b SSI_MODE_SLAVE_OD.)
	//TODO: Figure out why bitRate is stuck at such tiny numbers/how to get over "invalid size for bitfield" error
	uint32_t bitRate 		: 31; 		///<Master mode, bit rate must statisfy FSSI >= 2 * bitRate
	uint8_t dataWidth		: 8; 		///<Width of data transfers, num of bits per frame
}hal_spi_settings_t;
  
// This must be included after hal_spi_settings_t so that spi.h can find that definition
#include "spi.h"

/*
From Tiva C TM4C123 Datasheet page 952:
The TM4C123GH6PM microcontroller includes four Synchronous Serial Interface (SSI) modules.
Each SSI module is a master or slave interface for synchronous serial communication with peripheral
devices that have either Freescale SPI, MICROWIRE, or Texas Instruments synchronous serial
interfaces.

See page 954 for list of SSI pins and functions on all four SSI modules

Names are whatever, so far this seems correct. Define example USE_SPI_A0 in main.c and the USE_SPI0 is used internally for hal_spi.c and library's spi.c

*/
#ifdef USE_SPI_A0
#warning "Pins PA[5:2] of Tiva C are GPIO locked. If you don't know how to unlock those pins, you should pick a different SSI module. SSI2 is my favorite"
#define USE_SPI0
#endif

#ifdef USE_SPI_A1
#define USE_SPI1
#endif

#ifdef USE_SPI_B0
#define USE_SPI2
#endif

#ifdef USE_SPI_B1
#define USE_SPI3
#endif

#define SPI_A0 0 ///< index for SPI module A0
#define SPI_A1 1 ///< index for SPI module A1
#define SPI_B0 2 ///< index for SPI module B0
#define SPI_B1 3 ///< index for SPI module B1

///@}
#endif //_HAL_SPI_H_  
  
