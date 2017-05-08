//TODO Docs

#include "drawPokemon.h"
#include "pokemonImages.h"

void initDrawGraphics(){
    graphics_t* gptr = &gCntx; //TODO See if this is right
    Graphics_Init(gptr);
}

void drawPlayer(playerSprite ps, walkState ws, uint8_t locX, uint8_t locY){
	g_point_t pt;

	switch(ps){
		case AARON:
			switch(ws){
				case LEFT:
					//draw Aaron in left state at given location
					pt.x = locX * TILE_X;
					pt.y = locY * TILE_Y;
					Graphics_DrawTile(&gCntx, pt, &aaronLTilePtr, TILE_X, TILE_Y);
					break;
				case RIGHT:
					pt.x = locX * TILE_X;
					pt.y = locY * TILE_Y;
					Graphics_DrawTile(&gCntx, pt, &aaronRTilePtr, TILE_X, TILE_Y);
					break;
				case STAND:
					pt.x = locX * TILE_X;
					pt.y = locY * TILE_Y;
					Graphics_DrawTile(&gCntx, pt, &aaronSTilePtr, TILE_X, TILE_Y);
					break;
			}
			break;
		case BREANNA:
			switch(ws){
				case LEFT:
					pt.x = locX * TILE_X;
					pt.y = locY * TILE_Y;
					Graphics_DrawTile(&gCntx, pt, &breannaLTilePtr, TILE_X, TILE_Y);
					break;
				case RIGHT:
					pt.x = locX * TILE_X;
					pt.y = locY * TILE_Y;
					Graphics_DrawTile(&gCntx, pt, &breannaRTilePtr, TILE_X, TILE_Y);
					break;
				case STAND:
					pt.x = locX * TILE_X;
					pt.y = locY * TILE_Y;
					Graphics_DrawTile(&gCntx, pt, &breannaSTilePtr, TILE_X, TILE_Y);
					break;
			}
			break;
		case JOSH:
			switch(ws){
				case LEFT:
					pt.x = locX * TILE_X;
					pt.y = locY * TILE_Y;
					Graphics_DrawTile(&gCntx, pt, &joshLTilePtr, TILE_X, TILE_Y);
					break;
				case RIGHT:
					pt.x = locX * TILE_X;
					pt.y = locY * TILE_Y;
					Graphics_DrawTile(&gCntx, pt, &joshRTilePtr, TILE_X, TILE_Y);
					break;
				case STAND:
					pt.x = locX * TILE_X;
					pt.y = locY * TILE_Y;
					Graphics_DrawTile(&gCntx, pt, &joshSTilePtr, TILE_X, TILE_Y);
					break;
			}
			break;
		case WALT:
			switch(ws){
				case LEFT:
					pt.x = locX * TILE_X;
					pt.y = locY * TILE_Y;
					Graphics_DrawTile(&gCntx, pt, &waltLTilePtr, TILE_X, TILE_Y);
					break;
				case RIGHT:
					pt.x = locX * TILE_X;
					pt.y = locY * TILE_Y;
					Graphics_DrawTile(&gCntx, pt, &waltRTilePtr, TILE_X, TILE_Y);
					break;
				case STAND:
					pt.x = locX * TILE_X;
					pt.y = locY * TILE_Y;
					Graphics_DrawTile(&gCntx, pt, &waltSTilePtr, TILE_X, TILE_Y);
					break;
			}
			break;
	}
}

void drawGrass(grassState gs, uint8_t locX, uint8_t locY){
	g_point_t pt;
	pt.x = locX * TILE_X;
	pt.y = locY * TILE_Y;
	switch(gs){
	case GRASS:
		//update grid as well as draw one tile
		map.grid[locX + locY * TILE_Y] = grassTilePtr;
		Graphics_DrawTile(&gCntx, pt, &grassTilePtr, TILE_X, TILE_Y);
		break;
	case SHAKE:
		//update grid as well as draw one tile
		map.grid[locX + locY * TILE_Y] = shakingGrassTilePtr;
		Graphics_DrawTile(&gCntx, pt, &shakingGrassTilePtr, TILE_X, TILE_Y);
		break;
	}
}

void drawItem(uint8_t locX, uint8_t locY){
	g_point_t pt;
	pt.x = locX * TILE_X;
	pt.y = locY * TILE_Y;
	map.grid[locX + locY * TILE_Y] = itemTilePtr;
	Graphics_DrawTile(&gCntx, pt, &itemTilePtr, TILE_X, TILE_Y);
}

void drawMap(){
    map = (MapStruct){grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, rocksTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr,
                    grassTilePtr, grassTilePtr, treesTilePtr, treesTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr,
                    grassTilePtr, grassTilePtr, treesTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, treesTilePtr, treesTilePtr, grassTilePtr,
                    grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, treesTilePtr, rocksTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, treesTilePtr, grassTilePtr,
                    grassTilePtr, rocksTilePtr, grassTilePtr, groundTilePtr, groundTilePtr, groundTilePtr, groundTilePtr, groundTilePtr, groundTilePtr, grassTilePtr, treesTilePtr, grassTilePtr,
                    grassTilePtr, grassTilePtr, groundTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, groundTilePtr, grassTilePtr, grassTilePtr,
                    grassTilePtr, groundTilePtr, treesTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, treesTilePtr, grassTilePtr, grassTilePtr, groundTilePtr, grassTilePtr,
                    grassTilePtr, groundTilePtr, treesTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, groundTilePtr, grassTilePtr,
                    groundTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, groundTilePtr,
                    groundTilePtr, groundTilePtr, groundTilePtr, groundTilePtr, rocksTilePtr, groundTilePtr, groundTilePtr, rocksTilePtr, groundTilePtr, groundTilePtr, groundTilePtr, groundTilePtr,
                    groundTilePtr, groundTilePtr, groundTilePtr, groundTilePtr, rocksTilePtr, groundTilePtr, groundTilePtr, rocksTilePtr, groundTilePtr, groundTilePtr, groundTilePtr, groundTilePtr,
                    groundTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, groundTilePtr,
                    grassTilePtr, groundTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, groundTilePtr, grassTilePtr,
                    grassTilePtr, groundTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, treesTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, groundTilePtr, grassTilePtr,
                    grassTilePtr, grassTilePtr, groundTilePtr, grassTilePtr, grassTilePtr, rocksTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, groundTilePtr, grassTilePtr, grassTilePtr,
                    grassTilePtr, treesTilePtr, grassTilePtr, groundTilePtr, groundTilePtr, groundTilePtr, groundTilePtr, groundTilePtr, groundTilePtr, grassTilePtr, rocksTilePtr, treesTilePtr,
                    grassTilePtr, rocksTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr,
                    grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, rocksTilePtr, grassTilePtr, grassTilePtr, treesTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr,
                    grassTilePtr, treesTilePtr, treesTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, treesTilePtr, treesTilePtr, grassTilePtr, grassTilePtr, grassTilePtr,
                    grassTilePtr, grassTilePtr, treesTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, treesTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr
        };

    //adapted from Aaron's code in grTest main::drawMap(void)
    volatile int i, j;
    g_point_t pt;
    for (i = 0; i < GRID_X; i++) {
        for (j = 0; j < GRID_Y; j++) {
            pt.x = i * TILE_X;
            pt.y = j * TILE_Y;
            Graphics_DrawTile(&gCntx, pt, &map.grid[i + j * GRID_X], TILE_X, TILE_Y);
        }
    }
}
void drawStatic(const g_pixel_t* tileImg, g_point_t* pos){
	pos->x = pos->x * TILE_X;
	pos->y = pos->y * TILE_Y;
	Graphics_DrawTile(&gCntx, *pos, &tileImg, TILE_X, TILE_Y);
}
void drawInitMenu(void) {
	volatile int i, x, y;
	g_point_t p1, p2;
	uint8_t color[3];

	color[0] = 0xFF; color[1] = 0xFF; color[2] = 0xFF;
	Graphics_SetForeground(&gCntx, color);
	Graphics_SetBackground(&gCntx, color);

	for (x = GRID_X * TILE_X; x < (GRID_X + TEXT_TILES) * TILE_X; x++) {
		for (y = 0; y < HEIGHT; y++) {
			p1.x = x; p1.y = y;
			Graphics_DrawPixel(&gCntx, p1);
		}
	}

	for (i = 1; i < 5; i++) {
		p1.x = TILE_X * GRID_X;
		p1.y = TILE_Y * (MENU_HEIGHT * (i - 1));
		p2.x = TILE_X * (GRID_X + TEXT_TILES);
		p2.y = TILE_Y * (MENU_HEIGHT * (i));

		color[0] = 0x55; color[1] = 0x55; color[2] = 0x55;
		Graphics_SetForeground(&gCntx, color);
		Graphics_DrawRectangle(&gCntx, p1, p2);

		color[0] = 0x00; color[1] = 0x00; color[2] = 0x00;
		Graphics_SetForeground(&gCntx, color);
		p1.x += HORI_PADDING; p1.y += VERT_PADDING;
		Graphics_DrawText(&gCntx, p1, "Player %d: %d   ", i, 0);
	}
	p1.x = TILE_X * GRID_X;
	p1.y = TILE_Y * (MENU_HEIGHT * 4);
	p2.y = TILE_Y * GRID_Y;

	color[0] = 0x55; color[1] = 0x55; color[2] = 0x55;
	Graphics_SetForeground(&gCntx, color);
	Graphics_DrawRectangle(&gCntx, p1, p2);

}
void printScore(uint8_t playerID, uint16_t score) {
	g_point_t pt;
	uint8_t color[3];
	pt.x = TILE_X * GRID_X + HORI_PADDING;
	pt.y = TILE_Y * (MENU_HEIGHT * playerID) + VERT_PADDING;

	color[0] = 0x00; color[1] = 0x00; color[2] = 0x00;
	Graphics_SetForeground(&gCntx, color);

	color[0] = 0xFF; color[1] = 0xFF; color[2] = 0xFF;
	Graphics_SetBackground(&gCntx, color);

	Graphics_DrawText(&gCntx, pt, "Player %d: %d   ", playerID + 1, score);
}

void printPokemon(uint8_t playerID, pokeMsgType msgType, char* pokemon) {
	g_point_t pt;
	uint8_t color[3];
	pt.x = TILE_X * GRID_X + HORI_PADDING;
	pt.y = TILE_Y * (MENU_HEIGHT * playerID + 1) + VERT_PADDING;

	color[0] = 0x00; color[1] = 0x00; color[2] = 0x00;
	Graphics_SetForeground(&gCntx, color);

	color[0] = 0xFF; color[1] = 0xFF; color[2] = 0xFF;
	Graphics_SetBackground(&gCntx, color);

	switch(msgType){
	case FOUND_MSG:
		Graphics_DrawText(&gCntx, pt, "Found %s!                  ", pokemon);
		break;
	case RAN_MSG:
		Graphics_DrawText(&gCntx, pt, "%s ran!                  ", pokemon);
		break;
	case CAUGHT_MSG:
		Graphics_DrawText(&gCntx, pt, "Caught %s!                  ", pokemon);
		break;
    case POKEBALL_MSG:
        Graphics_DrawText(&gCntx, pt, "Picked up Pokeball!");
        break;
    case GREATBALL_MSG:
        Graphics_DrawText(&gCntx, pt, "Picked up Greatball!");
        break;
    case ULTRABALL_MSG:
        Graphics_DrawText(&gCntx, pt, "Picked up Ultraball!");
        break;
    case FULL_MSG:
        Graphics_DrawText(&gCntx, pt, "Your bag is full!");
        break;
	case NONE_MSG:
		Graphics_DrawText(&gCntx, pt, "                                                     ");
		break;
	}
}

void printMenu(uint8_t playerID, menuState ms, int8_t pb, int8_t gb, int8_t ub, char* text){
	g_point_t pt;
	uint8_t color[3];
	int8_t numBalls;

	pt.x = TILE_X * GRID_X + HORI_PADDING;
	pt.y = TILE_Y * (MENU_HEIGHT * (playerID) + 2) + VERT_PADDING;

	color[0] = 0x00; color[1] = 0x00; color[2] = 0x00;
	Graphics_SetForeground(&gCntx, color);

	color[0] = 0xFF; color[1] = 0xFF; color[2] = 0xFF;
	Graphics_SetBackground(&gCntx, color);

	if (pb > 0) {
		numBalls = pb;
	}
	else if (gb > 0) {
		numBalls = gb;
	}
	else if (ub > 0) {
		numBalls = ub;
	}
	else{
		numBalls = 0;
	}

	switch(ms) {
	case RUN_BALL:
		Graphics_DrawText(&gCntx, pt, "Select Ball: A Run: B       ");
		break;
	case BALL_SELECT:
		Graphics_DrawText(&gCntx, pt, "%s: %d                    ", text, numBalls);
		break;
	case NONE:
		Graphics_DrawText(&gCntx, pt, "                                                     ");
		break;
	default:
		break;
	}
}
void printEndStats(uint8_t playerInd, uint8_t playerStat){
	g_point_t pt;

	pt.x = TILE_X * GRID_X + HORI_PADDING + 1;
	pt.y = TILE_Y * (MENU_HEIGHT * 4) + VERT_PADDING;

	Graphics_DrawText(&gCntx, pt, "Game over!                            ");

	pt.x = TILE_X * GRID_X + HORI_PADDING + 2;
	pt.y = TILE_Y * (MENU_HEIGHT * 4) + VERT_PADDING;

	Graphics_DrawText(&gCntx, pt, "Player %d won with %d points!                       ", playerInd+1, playerStat);
}

void printTime(uint8_t time){
	g_point_t pt;

	pt.x = TILE_X * GRID_X + HORI_PADDING;
	pt.y = TILE_Y * (MENU_HEIGHT * 4) + VERT_PADDING;

	Graphics_DrawText(&gCntx, pt, "Time Remaining: %d     ", time);
}

bool isTreeTile(uint8_t locX, uint8_t locY){
	return map.grid[locX + locY*TILE_Y] == treesTilePtr;
}

bool isRockTile(uint8_t locX, uint8_t locY){
	return map.grid[locX + locY*TILE_Y] == rocksTilePtr;
}

bool isShakingGrass(uint8_t locX, uint8_t locY){
	return map.grid[locX + locY*TILE_Y] == shakingGrassTilePtr;
}

bool isGrass(uint8_t locX, uint8_t locY){
	return map.grid[locX + locY*TILE_Y] == grassTilePtr;
}

bool isGround(uint8_t locX, uint8_t locY){
	return map.grid[locX + locY*TILE_Y] == groundTilePtr;
}

bool isItem(uint8_t locX, uint8_t locY){
	return map.grid[locX + locY*TILE_Y] == itemTilePtr;
}
