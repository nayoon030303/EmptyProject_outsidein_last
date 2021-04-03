#pragma once
#include "DXUT.h"
#include "inputManager.h"
#include "pageManager.h"
#include "gameSystem.h"

/*page number*/
#define FIRST_PAGE 100
#define SECOND_PAGE 200
#define TITLE_PAGE 300



/*map*/
#define MAP_PROPERTY_EDGE 100
#define MAP_PROPERTY_EMPTY 200
#define MAP_PROPERTY_VISIT 300
#define MAP_PROPERTY_VISITING 400
#define MAP_PROPERTY_TEMP 500

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define WIDTH 601
#define HEIGHT 680
#define PLAYER_WIDTH 4
#define PLAYER_HEIGHT 4


/*pos*/
#define STARTX_POINT WINDOW_WIDTH/2-WIDTH/2
#define STARTY_POINT 200


extern PageManager pageManager;
extern GameSystem gameSystem;
extern DWORD* mapData;


extern int map[WIDTH * HEIGHT];
extern int binaryMap[WIDTH * HEIGHT];


//extern LPDIRECT3DTEXTURE9* tex;
//