//TODO Docs

#include "drawPokemon.h"
#include "pokemonImages.h"

void initDrawGraphics(){
    graphics_t* gptr = &gCntx; //TODO See if this is right
    Graphics_Init(gptr);
}

void drawPlayer(playerSprite ps, walkState ws, uint8_t locX, uint8_t locY){
    //TODO

	g_point_t pt;

	switch(ps){
		case AARON: //TODO
		case BREANNA:
			switch(ws){
				case LEFT:
					//draw Breanna in left state at given location
					pt.x = locX * TILE_X;
					pt.y = locY * TILE_Y;
					Graphics_DrawTile(&gCntx, pt, &breannaLTilePtr, TILE_X, TILE_Y);
					break;
				case RIGHT: //TODO
				case STAND: //TODO
			}
			break;
		case JOSH: //TODO
		case WALT: //TODO
	}
}

void drawGrass(grassState gs, uint8_t location){
    //TODO
}
void drawMap(){
    map = (MapStruct){grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, rocksTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr,
                    grassTilePtr, grassTilePtr, treesTilePtr, treesTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr,
                    grassTilePtr, grassTilePtr, treesTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, treesTilePtr, treesTilePtr, grassTilePtr,
                    grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, treesTilePtr, rocksTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, treesTilePtr, grassTilePtr,
                    grassTilePtr, rocksTilePtr, grassTilePtr, goundTilePtr, goundTilePtr, goundTilePtr, goundTilePtr, goundTilePtr, goundTilePtr, grassTilePtr, treesTilePtr, grassTilePtr,
                    grassTilePtr, grassTilePtr, goundTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, goundTilePtr, grassTilePtr, grassTilePtr,
                    grassTilePtr, goundTilePtr, treesTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, treesTilePtr, grassTilePtr, grassTilePtr, goundTilePtr, grassTilePtr,
                    grassTilePtr, goundTilePtr, treesTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, goundTilePtr, grassTilePtr,
                    goundTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, goundTilePtr,
                    goundTilePtr, goundTilePtr, goundTilePtr, goundTilePtr, rocksTilePtr, goundTilePtr, goundTilePtr, rocksTilePtr, goundTilePtr, goundTilePtr, goundTilePtr, goundTilePtr,
                    goundTilePtr, goundTilePtr, goundTilePtr, goundTilePtr, rocksTilePtr, goundTilePtr, goundTilePtr, rocksTilePtr, goundTilePtr, goundTilePtr, goundTilePtr, goundTilePtr,
                    goundTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, goundTilePtr,
                    grassTilePtr, goundTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, goundTilePtr, grassTilePtr,
                    grassTilePtr, goundTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, treesTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, goundTilePtr, grassTilePtr,
                    grassTilePtr, grassTilePtr, goundTilePtr, grassTilePtr, grassTilePtr, rocksTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, goundTilePtr, grassTilePtr, grassTilePtr,
                    grassTilePtr, treesTilePtr, grassTilePtr, goundTilePtr, goundTilePtr, goundTilePtr, goundTilePtr, goundTilePtr, goundTilePtr, grassTilePtr, rocksTilePtr, treesTilePtr,
                    grassTilePtr, rocksTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr,
                    grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, rocksTilePtr, grassTilePtr, grassTilePtr, treesTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr,
                    grassTilePtr, treesTilePtr, treesTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, treesTilePtr, treesTilePtr, grassTilePtr, grassTilePtr, grassTilePtr,
                    grassTilePtr, grassTilePtr, treesTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, treesTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr
        };

    //BlockInterrupts();
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
    //RestoreInterrupts();
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
		p1.x++; p1.y++;
		Graphics_DrawText(&gCntx, p1, "Player %d: %d", i, 0);
	}
}
void printMenu(uint8_t playerID, menuState ms, char* text){

    //TODO
}
void printStats(uint8_t time, char* text){
    //TODO
}
