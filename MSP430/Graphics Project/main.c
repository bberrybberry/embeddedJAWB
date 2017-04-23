// System Includes
#include <msp430f5529.h>
#include <stdint.h>

//GrLib Includes
#include "grlib.h"
#include "driverlib.h"

// Embedded Library Includes
#include "system.h"
#include "game_controller_host.h"
#include "game_controller.h"
#include "game.h"
#include "uart.h"
#include "hal_general.h"
#include "hal_uart.h"
#include "task.h"
#include "timing.h"
#include "terminal.h"
#include "random_int.h"

//Custom Includes
#include "graphics.h"
#include "pixel_defs.h"
#include "map.h"

#define BORDER_THICKNESS	5
#define MAX_DEBRIS 			35
#define SECOND 				1000
#define CUR_PLAYER 			0
#define MIN_PERIOD 			50
#define MAX_PERIOD 			200
#define MAX_JUNK_SIZE		5
#define DIFF_TIME			5


#define	MOVE_X_INC_AMT		TILE_X
#define	MOVE_Y_INC_AMT		TILE_Y

//#define MOVE_RECTANGLE
#define MOVE_CHARACTER

graphics_t gCntx;

g_point_t p1, p2;
g_point_t t1, t2;

void boardInit(void);
void clockInit(void);
void timerInit(void);
void buttonCallbacks(void);
void printTime(void);

void populateMap(void);
void drawMap(void);

void aPressed(controller_buttons_t input, void* handle);
void bPressed(controller_buttons_t input, void* handle);
void startPressed(controller_buttons_t input, void* handle);
void upPressed(controller_buttons_t input, void* handle);
void downPressed(controller_buttons_t input, void* handle);
void leftPressed(controller_buttons_t input, void* handle);
void rightPressed(controller_buttons_t input, void* handle);

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	volatile int i = 0;

    boardInit();
	clockInit();
	//timerInit();

	Graphics_Init(&gCntx);

	EnableInterrupts();

	Timing_Init();
	Task_Init();
	UART_Init(0);
	UART_Init(1);

	GameControllerHost_Init();
	buttonCallbacks();

	uint8_t color[3];
	color[0] = 0xFF; color[1] = 0xFF; color[2] = 0xFF;
	Graphics_SetForeground(&gCntx, color);

	Graphics_Init(&gCntx);


	populateMap();
	drawMap();

	t1.x = 5;
	t1.y = 5;
	p1.x = t1.x * TILE_X;
	p1.y = t1.y * TILE_Y;
	Graphics_DrawTile(&gCntx, p1, &gPSTilePtr, TILE_X, TILE_Y);

	Task_Schedule(printTime, 0, 1000, 1000);

	while(1) {
		SystemTick();
	}

	return 0;
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

void timerInit(void)
{
    Timer_A_initUpModeParam timerAUpModeParams =
    {
        TIMER_A_CLOCKSOURCE_SMCLK,
        TIMER_A_CLOCKSOURCE_DIVIDER_64,
        UINT16_MAX,
        TIMER_A_TAIE_INTERRUPT_DISABLE,
        TIMER_A_CCIE_CCR0_INTERRUPT_DISABLE,
        TIMER_A_SKIP_CLEAR
    };
    //Configure timer A to count cycles/64
    Timer_A_initUpMode(
        TIMER_A1_BASE,&timerAUpModeParams);
}

void buttonCallbacks(void) {
	controller_buttons_t mask;

	mask.all_buttons = 0x0000;
	mask.button.A = 1;
	GameControllerHost_RegisterPressCallback(0, aPressed, mask, 0);
	mask.all_buttons = 0x0000;
	mask.button.B = 1;
	GameControllerHost_RegisterPressCallback(0, bPressed, mask, 0);
	mask.all_buttons = 0x0000;
	mask.button.start = 1;
	GameControllerHost_RegisterPressCallback(0, startPressed, mask, 0);
	mask.all_buttons = 0x0000;
	mask.button.up = 1;
	GameControllerHost_RegisterPressCallback(0, upPressed, mask, 0);
	mask.all_buttons = 0x0000;
	mask.button.down = 1;
	GameControllerHost_RegisterPressCallback(0, downPressed, mask, 0);
	mask.all_buttons = 0x0000;
	mask.button.left = 1;
	GameControllerHost_RegisterPressCallback(0, leftPressed, mask, 0);
	mask.all_buttons = 0x0000;
	mask.button.right = 1;
	GameControllerHost_RegisterPressCallback(0, rightPressed, mask, 0);
}

void printTime(void) {
	p2.x = 16; p2.y = 12;
	setFont(&g_sFontCmss12);
	Graphics_DrawText(&gCntx, p2, "Time: %lu s  ", TimeNow() / 1000);
}

void populateMap(void) {
	volatile int i;
	for (i = 0; i < GRID_X * GRID_Y; i++) {
		if (i % 6) {
			map[i] = whiteTilePtr;
		}
		else {
			map[i] = blackTilePtr;
		}
	}
}

void drawMap(void) {
	volatile int i, j;
	g_point_t pt;
	for (i = 0; i < GRID_X; i++) {
		for (j = 0; j < GRID_Y; j++) {
			pt.x = i * WHITE16X12_TILE_X;
			pt.y = j * WHITE16X12_TILE_Y;
			Graphics_DrawTile(&gCntx, pt, &map[i + j * GRID_X], WHITE16X12_TILE_X, WHITE16X12_TILE_Y);
		}
	}
}

void aPressed(controller_buttons_t input, void* handle) {
	//g_point_t p1;//, p2;
	//p1.x = 100; p1.y = 100;
//	p2.x = 50; p2.y = 50;

//	uint8_t c[3] = {0x00, 0x00, 0xFF};
//	Graphics_SetForeground(&gCntx, c);
//
//	Graphics_DrawRectangle(&gCntx, p1, p2);
	//Graphics_DrawText(&gCntx, p1,"Hello World!%d", 4);
	UART_Printf(CMC_UART_UPSTREAM, "A");
}

void bPressed(controller_buttons_t input, void* handle) {
//	g_point_t p1, p2;
//	p1.x = 0; p1. y = 0;
//	p2.x = 50; p2.y = 50;

	uint8_t c[3] = {0xFF, 0x00, 0x00};
	Graphics_SetForeground(&gCntx, c);

	//Graphics_DrawRectangle(&gCntx, p1, p2);
	UART_Printf(CMC_UART_UPSTREAM, "B");
}

void startPressed(controller_buttons_t input, void* handle) {

//	g_pixel_t* tilePtr = &grass[0];
//	g_point_t pt;
//	pt.x = 10;
//	pt.y = 10;
//	Graphics_DrawTile(&gCntx, pt, &tilePtr, TILE_X, TILE_Y);

	UART_Printf(CMC_UART_UPSTREAM, "S");
}

void upPressed(controller_buttons_t input, void* handle) {
#ifdef MOVE_RECTANGLE
	uint8_t c[3] = {0x00, 0x00, 0x00};
	Graphics_SetForeground(&gCntx, c);
	Graphics_DrawRectangle(&gCntx, p1, p2);

	if (p1.y > 0) {
		p1.y = p1.y - MOVE_INC_AMT;
		p2.y = p2.y - MOVE_INC_AMT;
	}

	c[0] = 0x00; c[1] = 0xFF; c[2] = 0x00;
	Graphics_SetForeground(&gCntx, c);
	Graphics_DrawRectangle(&gCntx, p1, p2);
#endif
#ifdef MOVE_CHARACTER

	if ((t1.y - 1) < GRID_Y ) {
		if (map[t1.x + t1.y * GRID_X]) {
			Graphics_DrawTile(&gCntx, p1, &map[t1.x + t1.y * GRID_X], TILE_X, TILE_Y);
		}
		else {
			Graphics_DrawTile(&gCntx, p1, &blackTilePtr, TILE_X, TILE_Y);
		}

		t1.y--;
		p1.y = t1.y * TILE_Y;
		Graphics_DrawTile(&gCntx, p1, &gPSTilePtr, TILE_X, TILE_Y);
	}

#endif
}

void downPressed(controller_buttons_t input, void* handle) {
#ifdef MOVE_RECTANGLE
	uint8_t c[3] = {0x00, 0x00, 0x00};
	Graphics_SetForeground(&gCntx, c);
	Graphics_DrawRectangle(&gCntx, p1, p2);

	if (p2.y < HEIGHT - 1) {
		p1.y = p1.y + MOVE_INC_AMT;
		p2.y = p2.y + MOVE_INC_AMT;
	}

	c[0] = 0x00; c[1] = 0xFF; c[2] = 0x00;
	Graphics_SetForeground(&gCntx, c);
	Graphics_DrawRectangle(&gCntx, p1, p2);
#endif
#ifdef MOVE_CHARACTER

	if (t1.y + 1 < GRID_Y) {
		if (map[t1.x + t1.y * GRID_X]) {
			Graphics_DrawTile(&gCntx, p1, &map[t1.x + t1.y * GRID_X], TILE_X, TILE_Y);
		}
		else {
			Graphics_DrawTile(&gCntx, p1, &blackTilePtr, TILE_X, TILE_Y);
		}

		t1.y++;
		p1.y = t1.y * TILE_Y;
		Graphics_DrawTile(&gCntx, p1, &gPSTilePtr, TILE_X, TILE_Y);
	}

#endif
}

void leftPressed(controller_buttons_t input, void* handle) {
#ifdef MOVE_RECTANGLE
	uint8_t c[3] = {0x00, 0x00, 0x00};
	Graphics_SetForeground(&gCntx, c);
	Graphics_DrawRectangle(&gCntx, p1, p2);

	if (p1.x > 0) {
		p1.x = p1.x - MOVE_INC_AMT;
		p2.x = p2.x - MOVE_INC_AMT;
	}

	c[0] = 0x00; c[1] = 0xFF; c[2] = 0x00;
	Graphics_SetForeground(&gCntx, c);
	Graphics_DrawRectangle(&gCntx, p1, p2);
#endif
#ifdef MOVE_CHARACTER

	if ((t1.x - 1) < GRID_X) {
		if (map[t1.x + t1.y * GRID_X]) {
			Graphics_DrawTile(&gCntx, p1, &map[t1.x + t1.y * GRID_X], TILE_X, TILE_Y);
		}
		else {
			Graphics_DrawTile(&gCntx, p1, &blackTilePtr, TILE_X, TILE_Y);
		}

		t1.x--;
		p1.x = t1.x * TILE_X;
		Graphics_DrawTile(&gCntx, p1, &gPLTilePtr, TILE_X, TILE_Y);
	}

#endif
}

void rightPressed(controller_buttons_t input, void* handle) {
#ifdef MOVE_RECTANGLE
	uint8_t c[3] = {0x00, 0x00, 0x00};
	Graphics_SetForeground(&gCntx, c);
	Graphics_DrawRectangle(&gCntx, p1, p2);

	if (p2.x < WIDTH - 2) {
		p1.x = p1.x + MOVE_INC_AMT;
		p2.x = p2.x + MOVE_INC_AMT;
	}

	c[0] = 0x00; c[1] = 0xFF; c[2] = 0x00;
	Graphics_SetForeground(&gCntx, c);
	Graphics_DrawRectangle(&gCntx, p1, p2);
#endif
#ifdef MOVE_CHARACTER

	if (t1.x + 1 < GRID_X) {
		if (map[t1.x + t1.y * GRID_X]) {
			Graphics_DrawTile(&gCntx, p1, &map[t1.x + t1.y * GRID_X], TILE_X, TILE_Y);
		}
		else {
			Graphics_DrawTile(&gCntx, p1, &blackTilePtr, TILE_X, TILE_Y);
		}

		t1.x++;
		p1.x = t1.x * TILE_X;
		Graphics_DrawTile(&gCntx, p1, &gPRTilePtr, TILE_X, TILE_Y);
	}

#endif
}
