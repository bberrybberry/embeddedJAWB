/**
 * Tiva C TM4C123 SPI Hal Layer WIP
 * Based on MSP430 SPI Hal at hal_spi as well as CC3200 also hal_spi.
 *
 * This will use Freescale style SPI settings on Tiva C SSI peripheral (?)
 */
 
#include "hal_spi.h"
 
//TODO: Rewrite msp code for tiva
void hal_SPI_Init(spi_settings_t* settings){
	// Disable
	// hal_SPI_Disable(settings->channel);
	switch(settings->channel){
		case SPI_A0: //SSI0
#warning "Pins PA[5:2] of Tiva C need to be unlocked before they can be used"
			//Configure peripheral
			SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);
			SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
		
			//Configure pins on SSI0
			GPIOPinConfigure(GPIO_PA2_SSI0CLK);
			GPIOPinConfigure(GPIO_PA3_SSI0FSS);
			GPIOPinConfigure(GPIO_PA4_SSI0RX); //MISO
			GPIOPinConfigure(GPIO_PA5_SSI0TX); //MOSI
			GPIOPinTypeSSI(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_4 | GPIO_PIN_3 | GPIO_PIN_2);
			
			//Enable SSI for SPI
			SSIConfigSetExpClk(SSI0_BASE, 		//SSI module base address 
					SysCtlClockGet(), 			//Clock rate supplied to SSI module
					SSI_FRF_MOTO_MODE_0, 		//data transfer protocol: Freescale Motorola on SSI0, this sets phase and polarity, see datasheet for frame format information beginning page 956 in section 15.3.4
					settings->hal_settings.modeOfOperation,		//mode of operation
					settings->hal_settings.bitRate,				//clock rate/bit rate
					settings->hal_settings.dataWidth			//number of bits per frame
			);
	
			break;
		case SPI_A1: //SSI1
		//This one is really weird. You just shouldn't use it.

			//Configure peripheral
			SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI1);
			SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
		
			//Configure pins on SSI1
			GPIOPinConfigure(GPIO_PF2_SSI1CLK);
			GPIOPinConfigure(GPIO_PF3_SSI1FSS);
			GPIOPinConfigure(GPIO_PF0_SSI1RX); //MISO
			GPIOPinConfigure(GPIO_PF1_SSI1TX); //MOSI
			GPIOPinTypeSSI(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
			
			//Enable SSI for SPI 
			SSIConfigSetExpClk(SSI1_BASE, 		//SSI module base address 
					SysCtlClockGet(), 			//Clock rate supplied to SSI module
					SSI_FRF_MOTO_MODE_0, 		//data transfer protocol: Freescale Motorola on SSI0, this sets phase and polarity, see datasheet for frame format information beginning page 956 in section 15.3.4
					settings->hal_settings.modeOfOperation,		//mode of operation
					settings->hal_settings.bitRate,				//clock rate/bit rate
					settings->hal_settings.dataWidth			//number of bits per frame
			);

			break;
		case SPI_B0: //SSI2

			//Configure peripheral
			SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI2);
			SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
		
			//Configure pins on SSI2
			GPIOPinConfigure(GPIO_PB4_SSI2CLK);
			GPIOPinConfigure(GPIO_PB5_SSI2FSS);
			GPIOPinConfigure(GPIO_PB6_SSI2RX); //MISO
			GPIOPinConfigure(GPIO_PB7_SSI2TX); //MOSI
			GPIOPinTypeSSI(GPIO_PORTB_BASE, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);
			
			//Enable SSI for SPI
			SSIConfigSetExpClk(SSI2_BASE, 		//SSI module base address 
					SysCtlClockGet(), 			//Clock rate supplied to SSI module
					SSI_FRF_MOTO_MODE_0, 		//data transfer protocol: Freescale Motorola on SSI0, this sets phase and polarity, see datasheet for frame format information beginning page 956 in section 15.3.4
					settings->hal_settings.modeOfOperation,		//mode of operation
					settings->hal_settings.bitRate,				//clock rate/bit rate
					settings->hal_settings.dataWidth			//number of bits per frame
			);
			break;
		case SPI_B1: //SSI3

			//Configure peripheral
			SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI3);
			SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
		
			//Configure pins on SSI3
			GPIOPinConfigure(GPIO_PD0_SSI3CLK);
			GPIOPinConfigure(GPIO_PD1_SSI3FSS);
			GPIOPinConfigure(GPIO_PD2_SSI3RX); //MISO
			GPIOPinConfigure(GPIO_PD3_SSI3TX); //MOSI
			GPIOPinTypeSSI(GPIO_PORTD_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
			
			//Enable SSI for SPI
			SSIConfigSetExpClk(SSI3_BASE, 						//SSI module base address
					SysCtlClockGet(), 							//Clock rate supplied to SSI module
					SSI_FRF_MOTO_MODE_0, 						//data transfer protocol: Freescale Motorola on SSI0, this sets phase and polarity, see datasheet for frame format information beginning page 956 in section 15.3.4
					settings->hal_settings.modeOfOperation,		//mode of operation
					settings->hal_settings.bitRate,				//clock rate/bit rate
					settings->hal_settings.dataWidth			//number of bits per frame
			);
			break;
		
	}
	// hal_SPI_Enable(settings->channel);
	// hal_SPI_ClearRxIF(settings->channel);
	// hal_SPI_EnableRxInterrupt(settings->channel);
}

void hal_SPI_Enable(uint8_t channel){
	//Var to hold garbage data
	uint32_t dataCleaner[31]; //TODO: Put a logical/dynamic value here instead of random 31
	
	switch(settings->channel){
		case SPI_A0: //SSI0
			//Enable module
			SSIEnable(SSI0_BASE);
	
			//From spi_master.c in tivaware/examples/peripherals:
			//
			// Read any residual data from the SSI port.  This makes sure the receive
			// FIFOs are empty, so we don't read any unwanted junk.  This is done here
			// because the SPI SSI mode is full-duplex, which allows you to send and
			// receive at the same time.  The SSIDataGetNonBlocking function returns
			// "true" when data was returned, and "false" when no data was returned.
			// The "non-blocking" function checks if there is any data in the receive
			// FIFO and does not "hang" if there isn't.
			//
			while(SSIDataGetNonBlocking(SSI0_BASE, &dataCleaner[0]))
			{
			}
	
			break;
		case SPI_A1: //SSI1
		//This one is really weird. You just shouldn't use it.
		
			//Enable module
			SSIEnable(SSI1_BASE);
	
			//From spi_master.c in tivaware/examples/peripherals:
			//
			// Read any residual data from the SSI port.  This makes sure the receive
			// FIFOs are empty, so we don't read any unwanted junk.  This is done here
			// because the SPI SSI mode is full-duplex, which allows you to send and
			// receive at the same time.  The SSIDataGetNonBlocking function returns
			// "true" when data was returned, and "false" when no data was returned.
			// The "non-blocking" function checks if there is any data in the receive
			// FIFO and does not "hang" if there isn't.
			//
			while(SSIDataGetNonBlocking(SSI1_BASE, &dataCleaner[0]))
			{
			}

			break;
		case SPI_B0: //SSI2
	
			//Enable module
			SSIEnable(SSI1_BASE);
	
			//From spi_master.c in tivaware/examples/peripherals:
			//
			// Read any residual data from the SSI port.  This makes sure the receive
			// FIFOs are empty, so we don't read any unwanted junk.  This is done here
			// because the SPI SSI mode is full-duplex, which allows you to send and
			// receive at the same time.  The SSIDataGetNonBlocking function returns
			// "true" when data was returned, and "false" when no data was returned.
			// The "non-blocking" function checks if there is any data in the receive
			// FIFO and does not "hang" if there isn't.
			//
			while(SSIDataGetNonBlocking(SSI2_BASE, &dataCleaner[0]))
			{
			}
			break;
		case SPI_B1: //SSI3
	
			//Enable module
			SSIEnable(SSI3_BASE);
	
			//From spi_master.c in tivaware/examples/peripherals:
			//
			// Read any residual data from the SSI port.  This makes sure the receive
			// FIFOs are empty, so we don't read any unwanted junk.  This is done here
			// because the SPI SSI mode is full-duplex, which allows you to send and
			// receive at the same time.  The SSIDataGetNonBlocking function returns
			// "true" when data was returned, and "false" when no data was returned.
			// The "non-blocking" function checks if there is any data in the receive
			// FIFO and does not "hang" if there isn't.
			//
			while(SSIDataGetNonBlocking(SSI3_BASE, &dataCleaner[0]))
			{
			}
			break;
		
	}
}

void hal_SPI_Disable(uint8_t channel){
	switch(channel){
		case SPI_A0: //SSI0
			SSIDisable(SSI0_BASE);
			break;
		case SPI_A1: //SSI1
			SSIDisable(SSI1_BASE);
			break;
		case SPI_B0: //SSI2
			SSIDisable(SSI1_BASE);
			break;
		case SPI_B1: //SSI3
			SSIDisable(SSI3_BASE);
			break;

	}
}

uint8_t hal_SPI_SpaceAvailable(uint8_t channel){
	//TODO
}

uint8_t hal_SPI_DataAvailable(uint8_t channel){
	//TODO
}

void hal_SPI_ClearRxIF(uint8_t channel){
	//TODO
}

void hal_SPI_ClearTxIF(uint8_t channel){
	//TODO
}

void hal_SPI_EnableRxInterrupt(uint8_t channel){
	//TODO
}

void hal_SPI_EnableTxInterrupt(uint8_t channel){
	//TODO
}

void hal_SPI_DisableRxInterrupt(uint8_t channel){
	//TODO
}

void hal_SPI_DisableTxInterrupt(uint8_t channel){
	//TODO
}

uint8_t hal_SPI_TxIntStatus(uint8_t channel){
	//TODO
}

uint8_t hal_SPI_RxIntStatus(uint8_t channel){
	//TODO
}

uint8_t hal_SPI_IsTxIntEnabled(uint8_t channel){
	//TODO
}

uint8_t hal_SPI_RxByte(uint8_t channel){
	//TODO
}

void hal_SPI_TxByte(uint8_t channel, uint8_t b){
	//TODO
}

uint8_t hal_SPI_OverrunError(uint8_t channel){
	//TODO
}

	
	
	
//TODO: Rewrite msp code for tiva
// void hal_SPI_Enable(uint8_t channel){
	// switch(channel){
		// case SPI_A0:
			// UCA0CTL1 &= ~(UCSWRST);
			// break;
		// case SPI_A1:
			// UCA1CTL1 &= ~(UCSWRST);
			// break;
		// case SPI_B0:
			// UCB0CTL1 &= ~(UCSWRST);
			// break;
		// case SPI_B1:
			// UCB1CTL1 &= ~(UCSWRST);
			// break;
		// default:
			// return;
	// }
// }


// void hal_SPI_Disable(uint8_t channel){
	// switch(channel){
		// case SPI_A0:
			// UCA0CTL1 |= UCSWRST;
			// break;
		// case SPI_A1:
			// UCA1CTL1 |= UCSWRST;
			// break;
		// case SPI_B0:
			// UCB0CTL1 |= UCSWRST;
			// break;
		// case SPI_B1:
			// UCB1CTL1 |= UCSWRST;
			// break;
		// default:
			// return;
	// }
// }


// void hal_SPI_EnableRxInterrupt(uint8_t channel){
	// switch(channel){
		// case SPI_A0:
			// UCA0IE |= UCRXIE;
			// break;
		// case SPI_A1:
			// UCA1IE |= UCRXIE;
			// break;
		// case SPI_B0:
			// UCB0IE |= UCRXIE;
			// break;
		// case SPI_B1:
			// UCB1IE |= UCRXIE;
			// break;
		// default:
			// return;
	// }
// }


// void hal_SPI_EnableTxInterrupt(uint8_t channel){
	// switch(channel){
		// case SPI_A0:
			// UCA0IE |= UCTXIE;
			// break;
		// case SPI_A1:
			// UCA1IE |= UCTXIE;
			// break;
		// case SPI_B0:
			// UCB0IE |= UCTXIE;
			// break;
		// case SPI_B1:
			// UCB1IE |= UCTXIE;
			// break;
		// default:
			// return;
	// }
// }


// void hal_SPI_DisableRxInterrupt(uint8_t channel){
	// switch(channel){
		// case SPI_A0:
			// UCA0IE &= ~UCRXIE;
			// break;
		// case SPI_A1:
			// UCA1IE &= ~UCRXIE;
			// break;
		// case SPI_B0:
			// UCB0IE &= ~UCRXIE;
			// break;
		// case SPI_B1:
			// UCB1IE &= ~UCRXIE;
			// break;
		// default:
			// return;
	// }
// }


// void hal_SPI_DisableTxInterrupt(uint8_t channel){
	// switch(channel){
		// case SPI_A0:
			// UCA0IE &= ~UCTXIE;
			// break;
		// case SPI_A1:
			// UCA1IE &= ~UCTXIE;
			// break;
		// case SPI_B0:
			// UCB0IE &= ~UCTXIE;
			// break;
		// case SPI_B1:
			// UCB1IE &= ~UCTXIE;
			// break;
		// default:
			// return;
	// }
// }


// uint8_t hal_SPI_TxIntStatus(uint8_t channel){
	// switch(channel){
		// case SPI_A0:
			// return (UCA0IFG & UCTXIFG) >> 1;
		// case SPI_A1:
			// return (UCA1IFG & UCTXIFG) >> 1;
		// case SPI_B0:
			// return (UCB0IFG & UCTXIFG) >> 1;
		// case SPI_B1:
			// return (UCB1IFG & UCTXIFG) >> 1;
		// default:
			// return 0;
	// }
// }


// uint8_t hal_SPI_IsTxIntEnabled(uint8_t channel){
	// switch(channel){
		// case SPI_A0:
			// return (UCA0IE & UCTXIE) >> 1;
		// case SPI_A1:
			// return (UCA1IE & UCTXIE) >> 1;
		// case SPI_B0:
			// return (UCB0IE & UCTXIE) >> 1;
		// case SPI_B1:
			// return (UCB1IE & UCTXIE) >> 1;
		// default:
			// return 0;
	// }
// }


// uint8_t hal_SPI_RxIntStatus(uint8_t channel){
	// switch(channel){
		// case SPI_A0:
			// return (UCA0IFG & UCRXIFG);
		// case SPI_A1:
			// return (UCA1IFG & UCRXIFG);
		// case SPI_B0:
			// return (UCB0IFG & UCRXIFG);
		// case SPI_B1:
			// return (UCB1IFG & UCRXIFG);
		// default:
			// return 0;
	// }
// }


// void hal_SPI_TxByte(uint8_t channel, uint8_t b){
	// switch(channel){
		// case SPI_A0:
			// UCA0TXBUF = b;
			// break;
		// case SPI_A1:
			// UCA1TXBUF = b;
			// break;
		// case SPI_B0:
			// UCB0TXBUF = b;
			// break;
		// case SPI_B1:
			// UCB1TXBUF = b;
			// break;
		// default:
			// return;
	// }
// }


// uint8_t hal_SPI_RxByte(uint8_t channel){
	// switch(channel){
		// case SPI_A0:
			// return UCA0RXBUF;
		// case SPI_A1:
			// return UCA1RXBUF;
		// case SPI_B0:
			// return UCB0RXBUF;
		// case SPI_B1:
			// return UCB1RXBUF;
		// default:
			// return 0;
	// }
// }


// void hal_SPI_ClearRxIF(uint8_t channel){
	// switch(channel){
		// case SPI_A0:
			// UCA0IFG &= ~UCRXIFG;
			// break;
		// case SPI_A1:
			// UCA1IFG &= ~UCRXIFG;
			// break;
		// case SPI_B0:
			// UCB0IFG &= ~UCRXIFG;
			// break;
		// case SPI_B1:
			// UCB1IFG &= ~UCRXIFG;
			// break;
		// default:
			// return;
	// }
// }


// void hal_SPI_ClearTxIF(uint8_t channel){
	// switch(channel){
		// case SPI_A0:
			// UCA0IFG &= ~UCTXIFG;
			// break;
		// case SPI_A1:
			// UCA1IFG &= ~UCTXIFG;
			// break;
		// case SPI_B0:
			// UCB0IFG &= ~UCTXIFG;
			// break;
		// case SPI_B1:
			// UCB1IFG &= ~UCTXIFG;
			// break;
		// default:
			// return;
	// }
// }


// uint8_t hal_SPI_SpaceAvailable(uint8_t channel){
	// switch(channel){
		// case SPI_A0:
			// return (UCA0IFG & UCTXIFG);
		// case SPI_A1:
			// return (UCA1IFG & UCTXIFG);
		// case SPI_B0:
			// return (UCB0IFG & UCTXIFG);
		// case SPI_B1:
			// return (UCB1IFG & UCTXIFG);
		// default:
			// return 0;
	// }
// }


// uint8_t hal_SPI_DataAvailable(uint8_t channel){
	// switch(channel){
		// case SPI_A0:
			// return (UCA0IFG & UCRXIFG);
		// case SPI_A1:
			// return (UCA1IFG & UCRXIFG);
		// case SPI_B0:
			// return (UCB0IFG & UCRXIFG);
		// case SPI_B1:
			// return (UCB1IFG & UCRXIFG);
		// default:
			// return 0;
	// }
// }


// uint8_t hal_SPI_OverrunError(uint8_t channel) {
	// switch(channel){
		// case SPI_A0:
			// return (UCA0STAT & UCOE);
		// case SPI_A1:
			// return (UCA1STAT & UCOE);
		// case SPI_B0:
			// return (UCB0STAT & UCOE);
		// case SPI_B1:
			// return (UCB1STAT & UCOE);
		// default:
			// return 0;
	// }
// }


// //TODO: Understand exactly what's this all doing?
// #ifdef USE_SPI0
// #ifdef MSPGCC
// __attribute__((interrupt(USCI_A0_VECTOR)))
// void _SPIA0_ISR(void) {
// #else
// #pragma vector=USCI_A0_VECTOR
// __interrupt void _SPIA0_ISR(void){
// #endif
	// SPI_ISR(SPI_A0);
// }
// #endif

// #ifdef USE_SPI1
// #ifdef MSPGCC
// __attribute__((interrupt(USCI_A1_VECTOR)))
// void _SPIA1_ISR(void) {
// #else
// #pragma vector=USCI_A1_VECTOR
// __interrupt void _SPIA1_ISR(void){
// #endif
	// SPI_ISR(SPI_A1);
// }
// #endif

// #ifdef USE_SPI2
// #ifdef MSPGCC
// __attribute__((interrupt(USCI_B0_VECTOR)))
// void _SPIB0_ISR(void) {
// #else
// #pragma vector=USCI_B0_VECTOR
// __interrupt void _SPIB0_ISR(void){
// #endif
	// SPI_ISR(SPI_B0);
// }
// #endif

// #ifdef USE_SPI3
// #ifdef MSPGCC
// __attribute__((interrupt(USCI_B1_VECTOR)))
// void _SPIB1_ISR(void) {
// #else
// #pragma vector=USCI_B1_VECTOR
// __interrupt void _SPIB1_ISR(void){
// #endif
	// SPI_ISR(SPI_B1);
// }
// #endif

