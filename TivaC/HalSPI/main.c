#include <stdbool.h>
#include <stdint.h>

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/ssi.h"


#include "system.h"
#include "nrf24.h"
#include "timing.h"
#include "task.h"
#include "uart.h"
#include "spi.h"
#include "hal_general.h"
#include "game.h"
#include "game_muh3.h"

// add the following to system.h:
// #define USE_SPI2
// #define SPI_MAX_SIZE 33


/* TivaC TM4C123 RF1:
* - MISO PB6
* - MOSI PB7
* - SCK  PB4
* - CS   PE1//PB5 //SSIFss acts as chip select https://engineering.purdue.edu/ece477/Archive/2014/Spring/S14-Grp1/docs/software/LM4F-LaunchPad-11%20-%20SPI.pdf
* - CE   PE2
* - IRQ  PE3
*/

//Run SSI2 Module
#define RF_SPI_CH SPI_B0

void RF1_CE(uint8_t out);
void RF1_CSN(uint8_t out);
void RF1_PollIRQ(void);

//void RF1_Init(void);

nrf24_t RF1;

int main(void) {
    //WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    //set Tiva C clock to 24Mhz
	SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_24MHZ);

//    //Setup IRQ, CE, CSN for RF2
//	P7DIR |= BIT0; // CE as output
//	P2DIR |= BIT2; // CSN as output
//	P6DIR &= ~BIT4; // IRQ as input

    //Setup IRQ, CE, CSN for RF1
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_1|GPIO_PIN_2);
    GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PIN_3);
//    P2DIR |= BIT3 | BIT4; // CE, CSN as output
//    P2DIR &= ~BIT5; // IRQ as input

    DisableInterrupts();

    Timing_Init();
    Task_Init();
    UART_Init(SUBSYS_UART);

    spi_settings_t spi_settings;
    spi_settings.channel = RF_SPI_CH;
    spi_settings.bit_rate = 200000;
    spi_settings.hal_settings.bytesToSend = 8;
    spi_settings.hal_settings.modeOfOperation = SSI_MODE_MASTER;
    spi_settings.hal_settings.bitRate = spi_settings.bit_rate;
    spi_settings.hal_settings.dataWidth = 8;
//    spi_settings.hal_settings.char7bit = 0;
//    spi_settings.hal_settings.msb_first = 1;
    spi_settings.mode = 0;
    SPI_Init(&spi_settings);


    RF1_CSN(1);

    RF1.ce = RF1_CE;
    RF1.csn = RF1_CSN;
    RF1.spi_channel = RF_SPI_CH;

    MUH3_Init();
    Game_nRF_Test_Init();
    Game_NetworkInit(&RF1);
    Log_EchoOn();
    UART_Printf(SUBSYS_UART, "System Initialized\r\n");

    EnableInterrupts();

	while(1){
		SystemTick();
		RF1_PollIRQ();
	}
}

// This function is provided to the network layer in the init function and is used to control the
// Chip Enable pin on the radio
void RF1_CE(uint8_t out){
	//CE is PE2
	GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2, out << 4);
//	P2OUT = (P2OUT & ~BIT4) | (out << 4);
}

// This function is provided to the network layer in the init function and is used to control the
// Chip Select pin on the radio
void RF1_CSN(uint8_t out){
	//CSN is PE1
	GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, out << 3);
//	P2OUT = (P2OUT & ~BIT3) | (out << 3);
}

// Method to poll the interrupt pin and see if an interrupt has occured
void RF1_PollIRQ(void){
	//IRQ is PE3
	static uint8_t pin_state = 1;
	static uint32_t last = 0;
	uint8_t new_state = GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_3) >> 5;//(P2IN & BIT5) >> 5;

	if( (new_state != pin_state) && !new_state) {
		last = TimeNow();
		nRF24_ISR(&RF1);
	}else if(!new_state && TimeSince(last)>5) {
		last = TimeNow();
		nRF24_ISR(&RF1);
	}
	pin_state = new_state;
}

