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
void printMenu(uint8_t playerID, menuState ms, char* text){
    //TODO
}
void printStats(uint8_t time, char* text){
    //TODO
}

bool isTreeTile(uint8_t locX, uint8_t locY){
	return map.grid[locX + locY*TILE_Y] == treesTilePtr;
}

bool isRockTile(uint8_t locX, uint8_t locY){
	return map.grid[locX + locY*TILE_Y] == rocksTilePtr;
}
