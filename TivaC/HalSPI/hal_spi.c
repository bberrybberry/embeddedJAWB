/**
 * Tiva C TM4C123 SPI Hal Layer WIP
 * Based on MSP430 SPI Hal at hal_spi as well as CC3200 also hal_spi.
 *
 * This will use Freescale style SPI settings on Tiva C SSI peripheral (?)
 */
 
#include "hal_spi.h"
#include "inc/tm4c123gh6pm.h"

#ifdef USE_SPI0
#warning "Add SSI0_Handler to the TivaC Vector Table"
#endif
void SSI0_Handler(void){
	//Handle interrupt
	SPI_Rx_Handler(SPI_A0);
	SSIIntClear(SSI0_BASE, SSI_RXTO|SSI_RXOR);
	SPI_Tx_Handler(SPI_A0);
}

#ifdef USE_SPI1
#warning "Add SSI1_Handler to the TivaC Vector Table"
#endif
void SSI1_Handler(void){
	//Handle interrupt
	SPI_Rx_Handler(SPI_A1);
	SSIIntClear(SSI1_BASE, SSI_RXTO|SSI_RXOR);
	SPI_Tx_Handler(SPI_A1);
}

#ifdef USE_SPI2
#warning "Add SSI2_Handler to the TivaC Vector Table"
#endif
void SSI2_Handler(void){
	//Handle interrupt
	SPI_Rx_Handler(SPI_B0);
	SSIIntClear(SSI2_BASE, SSI_RXTO|SSI_RXOR);
	SPI_Tx_Handler(SPI_B0);
}

#ifdef USE_SPI3
#warning "Add SSI3_Handler to the TivaC Vector Table"
#endif
void SSI3_Handler(void){
	//Handle interrupt
	SPI_Rx_Handler(SPI_B1);
	SSIIntClear(SSI3_BASE, SSI_RXTO|SSI_RXOR);
	SPI_Tx_Handler(SPI_B1);
}
 
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


			//Disable
			SSIDisable(SSI0_BASE);

			//Disable interrupts
			SSIIntDisable(SSI0_BASE, SSI_TXFF|SSI_RXFF|SSI_RXOR|SSI_RXTO);

			//Clear interrupts
			SSIIntClear(SSI0_BASE, SSI_RXTO|SSI_RXOR);

			//Register int handlers
			SSIIntRegister(SSI0_BASE, SSI0_Handler);

			//Enable SSI
			hal_SPI_Enable(settings->channel);

//			//Enable interrupts
//			SSIIntEnable(SSI0_BASE, SSI_TXFF|SSI_RXFF);
	
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


			//Disable
			SSIDisable(SSI1_BASE);

			//Disable interrupts
			SSIIntDisable(SSI1_BASE, SSI_TXFF|SSI_RXFF|SSI_RXOR|SSI_RXTO);

			//Clear interrupts
			SSIIntClear(SSI1_BASE, SSI_RXTO|SSI_RXOR);

			//Register int handlers
			SSIIntRegister(SSI1_BASE, SSI1_Handler);

			//Enable SSI
			hal_SPI_Enable(settings->channel);

//			//Enable interrupts
//			SSIIntEnable(SSI1_BASE, SSI_TXFF|SSI_RXFF);

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



			//Disable
			SSIDisable(SSI2_BASE);

			//Disable interrupts
			SSIIntDisable(SSI2_BASE, SSI_TXFF|SSI_RXFF|SSI_RXOR|SSI_RXTO);

			//Clear interrupts
			SSIIntClear(SSI2_BASE, SSI_RXTO|SSI_RXOR);

			//Register int handlers
			SSIIntRegister(SSI2_BASE, SSI2_Handler);

			//Enable SSI
			hal_SPI_Enable(settings->channel);

			//Enable interrupts
			SSIIntEnable(SSI2_BASE, SSI_TXFF|SSI_RXFF);

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


			//Disable
			SSIDisable(SSI3_BASE);

			//Disable interrupts
			SSIIntDisable(SSI3_BASE, SSI_TXFF|SSI_RXFF|SSI_RXOR|SSI_RXTO);

			//Clear interrupts
			SSIIntClear(SSI3_BASE, SSI_RXTO|SSI_RXOR);

			//Register int handlers
			SSIIntRegister(SSI3_BASE, SSI3_Handler);

			//Enable SSI
			hal_SPI_Enable(settings->channel);

//			//Enable interrupts
//			SSIIntEnable(SSI3_BASE, SSI_TXFF|SSI_RXFF);

			break;
		
	}
	// hal_SPI_Enable(settings->channel);
	// hal_SPI_ClearRxIF(settings->channel);
	// hal_SPI_EnableRxInterrupt(settings->channel);
}

void hal_SPI_Enable(uint8_t channel){
	//Var to hold garbage data
	uint32_t dataCleaner[31]; //TODO: Put a logical/dynamic value here instead of random 31
	
	switch(channel){
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
			SSIEnable(SSI2_BASE);
	
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
	//see if there's a pending transmit interrupt, if so return 1

	switch(channel){
		case SPI_A0:
			return (SSIBusy(SSI0_BASE)) ? 0: 1; //(UCA0IFG & UCTXIFG);
		case SPI_A1:
			return (SSIBusy(SSI1_BASE)) ? 0: 1; //(UCA1IFG & UCTXIFG);
		case SPI_B0:
			return (SSIBusy(SSI2_BASE)) ? 0: 1; //(UCB0IFG & UCTXIFG);
		case SPI_B1:
			return (SSIBusy(SSI3_BASE)) ? 0: 1; //(UCB1IFG & UCTXIFG);
		default:
			return 0;
	}
}

uint8_t hal_SPI_DataAvailable(uint8_t channel){
	//this guys job is to hold SOME data to see if there's any data there at all
	//I'm little afriad this means we'll lose data as this might pop the data out as it reads
	//oh well we'll figure it out
	uint32_t dataCleaner[31]; //TODO: Put a logical/dynamic value here instead of random 31

	//Receive interrupt flag. UCRXIFG is set when UCAxRXBUF has received a
	//complete character.
	//0b = No interrupt pending
	//1b = Interrupt pending

	//@return 0 if no data is available in receive buffer, non-zero if data is available

	switch(channel){
			case SPI_A0:
				return SSIDataGetNonBlocking(SSI0_BASE, dataCleaner);
			case SPI_A1:
				return SSIDataGetNonBlocking(SSI1_BASE, dataCleaner);
			case SPI_B0:
				return SSIDataGetNonBlocking(SSI2_BASE, dataCleaner);
			case SPI_B1:
				return SSIDataGetNonBlocking(SSI3_BASE, dataCleaner);
			default:
				return 0;
	}

}

void hal_SPI_ClearRxIF(uint8_t channel){

	switch(channel){
		case SPI_A0:
			SSIIntClear(SSI0_BASE, SSI_RXOR|SSI_RXTO);
		case SPI_A1:
			SSIIntClear(SSI1_BASE, SSI_RXOR|SSI_RXTO);
		case SPI_B0:
			SSIIntClear(SSI2_BASE, SSI_RXOR|SSI_RXTO);
		case SPI_B1:
			SSIIntClear(SSI3_BASE, SSI_RXOR|SSI_RXTO);
	}
}

void hal_SPI_ClearTxIF(uint8_t channel){
	//TODO figure out where the transmit interrupts actually are
	hal_SPI_ClearRxIF(channel);
}

void hal_SPI_EnableRxInterrupt(uint8_t channel){
	switch(channel){
		case SPI_A0:
			SSIIntEnable(SSI0_BASE, SSI_RXFF);
		case SPI_A1:
			SSIIntEnable(SSI1_BASE, SSI_RXFF);
		case SPI_B0:
			SSIIntEnable(SSI2_BASE, SSI_RXFF);
		case SPI_B1:
			SSIIntEnable(SSI3_BASE, SSI_RXFF);
	}
}

void hal_SPI_EnableTxInterrupt(uint8_t channel){
	switch(channel){
		case SPI_A0:
			SSIIntEnable(SSI0_BASE, SSI_TXFF);
		case SPI_A1:
			SSIIntEnable(SSI1_BASE, SSI_TXFF);
		case SPI_B0:
			SSIIntEnable(SSI2_BASE, SSI_TXFF);
		case SPI_B1:
			SSIIntEnable(SSI3_BASE, SSI_TXFF);
	}
}

void hal_SPI_DisableRxInterrupt(uint8_t channel){
	switch(channel){
		case SPI_A0:
			SSIIntDisable(SSI0_BASE, SSI_RXFF);
		case SPI_A1:
			SSIIntDisable(SSI1_BASE, SSI_RXFF);
		case SPI_B0:
			SSIIntDisable(SSI2_BASE, SSI_RXFF);
		case SPI_B1:
			SSIIntDisable(SSI3_BASE, SSI_RXFF);
	}
}

void hal_SPI_DisableTxInterrupt(uint8_t channel){
	switch(channel){
		case SPI_A0:
			SSIIntDisable(SSI0_BASE, SSI_TXFF);
		case SPI_A1:
			SSIIntDisable(SSI1_BASE, SSI_TXFF);
		case SPI_B0:
			SSIIntDisable(SSI2_BASE, SSI_TXFF);
		case SPI_B1:
			SSIIntDisable(SSI3_BASE, SSI_TXFF);
	}
}

uint8_t hal_SPI_TxIntStatus(uint8_t channel){
	switch(channel){
		case SPI_A0:
			return SSIIntStatus(SSI0_BASE, SSI_TXFF);
		case SPI_A1:
			return SSIIntStatus(SSI1_BASE, SSI_TXFF);
		case SPI_B0:
			return SSIIntStatus(SSI2_BASE, SSI_TXFF);
		case SPI_B1:
			return SSIIntStatus(SSI3_BASE, SSI_TXFF);
	}
}

uint8_t hal_SPI_RxIntStatus(uint8_t channel){
	switch(channel){
		case SPI_A0:
			return SSIIntStatus(SSI0_BASE, SSI_RXFF);
		case SPI_A1:
			return SSIIntStatus(SSI1_BASE, SSI_RXFF);
		case SPI_B0:
			return SSIIntStatus(SSI2_BASE, SSI_RXFF);
		case SPI_B1:
			return SSIIntStatus(SSI3_BASE, SSI_RXFF);
	}
}

uint8_t hal_SPI_IsTxIntEnabled(uint8_t channel){
	return 1;
}

uint8_t hal_SPI_RxByte(uint8_t channel){
	uint32_t data;
	switch(channel){
		case SPI_A0:
			SSIDataGet(SSI0_BASE, &data);
		case SPI_A1:
			SSIDataGet(SSI1_BASE, &data);
		case SPI_B0:
			SSIDataGet(SSI2_BASE, &data);
		case SPI_B1:
			SSIDataGet(SSI3_BASE, &data);
	}

	//I hope this works
	data = data & 0x00FF;
	return (uint8_t) data;
}

void hal_SPI_TxByte(uint8_t channel, uint8_t b){
	switch(channel){
		case SPI_A0:
			SSIDataPut(SSI0_BASE, b);
		case SPI_A1:
			SSIDataPut(SSI1_BASE, b);
		case SPI_B0:
			SSIDataPut(SSI2_BASE, b);
		case SPI_B1:
			SSIDataPut(SSI3_BASE, b);
	}
}

uint8_t hal_SPI_OverrunError(uint8_t channel){
	switch(channel){
		case SPI_A0:
			return (SSIIntStatus(SSI0_BASE, SSI_RXOR)) ? 1 : 0;
		case SPI_A1:
			return (SSIIntStatus(SSI0_BASE, SSI_RXOR)) ? 1 : 0;
		case SPI_B0:
			return (SSIIntStatus(SSI0_BASE, SSI_RXOR)) ? 1 : 0;
		case SPI_B1:
			return (SSIIntStatus(SSI0_BASE, SSI_RXOR)) ? 1 : 0;
	}
}

