/**
 * @file main
 * @mainpage
 * @author Aaron Guidarelli, Breanna Higgins, Walter Marroquin, Josh Velez
 * @brief Main file for Pokemon final multiplayer game
 *<br>
 * TODO: Docs and report<br>
 *<br>
 * Report:<br>
 * --Description of the initial goals and motivation of the project<br>
 * <br>
 * --The goal is to make a game that would be played on an external display <br>
 *   using an external controller. The game has to be multi-player as well <br>
 *   as capable to play on a network using an NRF chip. The motivation was <br>
 *   to make a game that each member of the group would enjoy and have fun <br>
 *   playing, so we decided to make a fun Pokemon minigame. We all loved and still <br>
 *   love Pokemon and we thought we would try to recreate the Pokemon Safari <br>
 *   Zone and turn into a multi-player competition. <br>
 *   <br>
 * --Picture(s) of your project (and video links)<br>
 * --Other relevant figures, tables, references, etc.<br>
 * <br>
 * --https://drive.google.com/drive/folders/0B00mA9dgfG39d05FRzBpb1lta0U?usp=sharing <br>
 * <br>
 * --Description of the operation and use of your project.<br>
 * <br>
 *   Our project is a replication/modification of the Pokemon Safari Zone. <br>
 *   You walk around in grass patches and Pokemon will randomly appear in which you <br>
 *   will have the chance to catch them. The "catch" is that you will be competing <br>
 *   with 1 to 3 other players to score as many points as you can in each timed round.
 *   Each round will be 2 minutes and every Pokemon you catch will grant you <br>
 *   a certain amount of points depending on how rare the Pokemon is. Also the rarer <br>
 *   the Pokemon the harder they are to catch. To catch the Pokemon you will be using <br>
 *   pokeballs, greatballs, and ultraballs. You will start with a set number of each, <br>
 *   but can run out. They will randomly appear on the map and you will have <br>
 *   to go and pick them up. The game is designed to be played using the Kinect, <br>
 *   as the controller, as well as being played on a 320x 240 LCD display, but it <br>
 *   will work with other controllers and will render on other screens. <br>
 *   <br>
 * --Discussion of the final results and conclusion about your project.<br>
 *   The game while working correctly had a lot of challenges while devlopement. <br>
 *   We encountered problems when we started implementing multiplayer specifically <br>
 *   that we used a lot of random number generators for item and Pokmeon spawning, as <br>
 *   well as catching Pokemon.This caused inconsitencies across the games, such as <br>
 *   someone finding a Pidgey in one game and a Pikachu in another. We also <br>
 *   encountered problems with connecting the Kinect to the game. But this is due to <br>
 *   the fact that the Kinect isnt that precise and there is no real fix for it. We <br>
 *   have encountered many problems with the NRF and the NRF libraries. In the end the <br>
 *   game is fun and relatively bug free.<br>
 *   <br>
 * --A subsection with your thoughts on the helpfulness of Slack.<br>
 * <br>
 *   Slack was a very useful tool to keep each other up to date as well as a <br>
 *   great communication tool. General is great to get class updates and <br>
 *   individual channels are great for talking about specifics for our project. <br>
 *   We also added a github bot to our slack channel. This allowed us, at a <br>
 *   glance to look at what commits have been pushed to our code. <br>
 *   <br>
 * --A subsection with your thoughts on the helpfulness of Trello.<br>
 * <br>
 *   As a group, we did not think Trello was very effectively used this semester. <br>
 *   In the beginning it was good to see when the Zybook assignments <br>
 *   and when the UART and blink functions were due, but after that Trello <br>
 *   seemed to be pushed away and not really used or even helpful. Slack took <br>
 *   over and kept us a lot more organized and up tp date on when things needed <br>
 *   to be completed.
 *--A subsection with our thoughts on github.<br>
 *<br>
 *  We utilized github extensively in our project. From the beginning we knew we <br>
 *  needed some sort of version control. This allowed us to work on the same code<br>
 *  while not always together. It also keeps track of changes which is very useful.<br>
 *<br>
 *<br>
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

