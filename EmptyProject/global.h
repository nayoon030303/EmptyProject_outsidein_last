#pragma once
#include "DXUT.h"
#include "inputManager.h"
#include "pageManager.h"

#define FIRST_PAGE 100
#define SECOND_PAGE 200
#define TITLE_PAGE 300
#define STARTX_POINT 1920/2
#define STARTY_POINT 200
#define WIDTH 601
#define HEIGHT 680

extern InputManager inputManager;
extern PageManager pageManager;

extern int map[WIDTH * HEIGHT];
extern int binaryMap[WIDTH * HEIGHT];
extern DWORD* mapData = new DWORD[WIDTH * HEIGHT];

//extern LPDIRECT3DTEXTURE9* tex;
//