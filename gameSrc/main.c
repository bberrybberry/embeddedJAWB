/**
 * @file main
 * @mainpage
 * @author Aaron Guidarelli, Breanna Higgins, Walter Marroquin, Josh Velez
 * @brief Main file for pokemon final multiplayer game
 *<br>
 * TODO: Docs and report<br>
 *<br>
 * Report:<br>
 * --Description of the initial goals and motivation of the project<br>
 * --The goal is to make a game that would be played on an external display
 * --using an external controller. The game has to be multi player as well
 * --as capable to play on a network using an NRF chip The motivation was
 * --to make a game that each member of the group would enjoy and have fun playing.
 * --Picture(s) of your project (and video links)<br>
 * --Other relevant figures, tables, references, etc.<br>
 * --design documents?
 * --Description of the operation and use of your project.<br>
 * --Discussion of the final results and conclusion about your project.<br>
 * --A subsection with your thoughts on the helpfulness of Slack.<br>
 * --Aaron G.
 * --Breanna H.
 * --Walter M. Slack was a very useful tool to keep each other up to date
 *             as well as a great communication tool. General is great to
 *             get class updates and individual channels are great for
 *             talking about specifics for our project.
 * --Josh V.
 * --A subsection with your thoughts on the helpfulness of Trello.<br>
 *<br>
 *<br>
 *<br>
 * CCS Project Structure:<br>
 * -project<br>
 * ----driverlib<br>
 * ------MSPF5xx<br>
 * ----GrLib<br>
 * ------fonts<br>
 * ------grlib<br>
 * ----images<br>
 * -------images.h, LPRocket, TI_Logo<br>
 * ----img<br>
 * -------[aaronL.h, aaronR.h, grass.h, etc.]<br>
 * ----LcdDriver<br>
 * -------grlib inlcude things (booster pack driver)<br>
 * --[MSP HAL and embedded lib]<br>
 * --main.c & system.h<br>
 * --[HAL graphics stuff]<br>
 * --[pokemon.h, pokemonGame.h, pokemonImages.h<br>
 */
#include <msp430.h>
#include <stdint.h>
#include "driverlib.h"
#include "system.h"
#include "nrf24.h"
#include "timing.h"
#include "task.h"
#include "uart.h"
#include "spi.h"
#include "hal_general.h"
#include "game.h"
#include "pokemonGame.h"
#include "game_controller_host.h"

// add the following to system.h:
// #define USE_SPI2
// #define SPI_MAX_SIZE 33

/* MSP430F5529 RF1:
* - MISO P3.1->4.2
* - MOSI P3.0->4.1
* - SCK  P3.2->4.3
* - CS   P2.3
* - CE   P2.4
* - IRQ  P2.5->6.4
*/

void clockInit(void);
void boardInit(void);

#define RF_SPI_CH SPI_B1

void RF1_CE(uint8_t out);
void RF1_CSN(uint8_t out);
void RF1_PollIRQ(void);

void RF1_Init(void);

nrf24_t RF1;

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    boardInit();
    clockInit();
    //init graphics
    initDrawGraphics();

    DisableInterrupts();

    Timing_Init();
    Task_Init();
	UART_Init(0);
    UART_Init(1);

//    //Setup IRQ, CE, CSN for RF2
//	P7DIR |= BIT0; // CE as output
//	P2DIR |= BIT2; // CSN as output
//	P6DIR &= ~BIT4; // IRQ as input

    //Setup IRQ, CE, CSN for RF1
    P2DIR |= BIT3 | BIT4; // CE, CSN as output
    //P2DIR &= ~BIT5; // IRQ as input
    P6DIR &= ~BIT4; // IRQ as input

    spi_settings_t spi_settings;
    spi_settings.channel = RF_SPI_CH;
    spi_settings.bit_rate = 200000;
    spi_settings.hal_settings.char7bit = 0;
    spi_settings.hal_settings.msb_first = 1;
    spi_settings.mode = 0;
    SPI_Init(&spi_settings);
	
	GameControllerHost_Init();
	
    RF1_CSN(1);

    RF1.ce = RF1_CE;
    RF1.csn = RF1_CSN;
    RF1.spi_channel = RF_SPI_CH;

    Game_nRF_Test_Init();
    pkmnGameInit(&RF1);
    Game_NetworkInit(&RF1);
    Log_EchoOn();
    UART_Printf(UART1, "System Initialized\r\n");

    EnableInterrupts();

	while(1){
		SystemTick();
		RF1_PollIRQ();
	}
}

// This function is provided to the network layer in the init function and is used to control the
// Chip Enable pin on the radio
void RF1_CE(uint8_t out){
	P2OUT = (P2OUT & ~BIT4) | (out << 4);
}

// This function is provided to the network layer in the init function and is used to control the
// Chip Select pin on the radio
void RF1_CSN(uint8_t out){
	P2OUT = (P2OUT & ~BIT3) | (out << 3);
}

// Method to poll the interrupt pin and see if an interrupt has occured
void RF1_PollIRQ(void){
	static uint8_t pin_state = 1;
	static uint32_t last = 0;
	uint8_t new_state = (P6IN & BIT4) >> 4;

	if( (new_state != pin_state) && !new_state) {
		last = TimeNow();
		nRF24_ISR(&RF1);
	}else if(!new_state && TimeSince(last)>5) {
		last = TimeNow();
		nRF24_ISR(&RF1);
	}
	pin_state = new_state;
}

void boardInit(void)
{
    // Setup XT1 and XT2
    GPIO_setAsPeripheralModuleFunctionInputPin(
        GPIO_PORT_P5,
        GPIO_PIN2 + GPIO_PIN3 +
        GPIO_PIN4 + GPIO_PIN5
        );
}

void clockInit(void)
{
    UCS_setExternalClockSource(
        32768,
        0);

    // Set Vcore to accomodate for max. allowed system speed
    PMM_setVCore(
        PMM_CORE_LEVEL_3
        );

    // Use 32.768kHz XTAL as reference
    UCS_turnOnLFXT1(
        UCS_XT1_DRIVE_3,
        UCS_XCAP_3
        );

    // Set system clock to max (25MHz)
    UCS_initFLLSettle(
        25000,
        762
        );

    SFR_enableInterrupt(
        SFR_OSCILLATOR_FAULT_INTERRUPT
        );
}

