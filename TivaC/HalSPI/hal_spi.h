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
#include "system.h"
 
 /**
  * @brief spi settings structure
  * TODO: Make this accurate for settings needed for Tiva C
  */
typedef struct hal_spi_settings_t {
	uint8_t char7bit : 1; ///< char7bit
	uint8_t msb_first : 1; ///< msb_first
}hal_spi_settings_t;
  
// This must be included after hal_spi_settings_t so that spi.h can find that definition
#include "spi.h"

//TODO: See how these USE_SPI_XY match up with actual Tiva C Pin functions

/*
From Tiva C TM4C123 Datasheet page 952:
The TM4C123GH6PM microcontroller includes four Synchronous Serial Interface (SSI) modules.
Each SSI module is a master or slave interface for synchronous serial communication with peripheral
devices that have either Freescale SPI, MICROWIRE, or Texas Instruments synchronous serial
interfaces.

See page 954 for list of SSI pins and functions on all four SSI modules

Names are whatever, so far this seems correct. Define example USE_SPI_A0 in main.c and the USE_SPI0 is used internally for hal_spi.c

*/
#ifdef USE_SPI_A0
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
  