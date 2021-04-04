#pragma once
#include "DXUT.h"
#include "player.h"
#include "global.h"


class GameSystem
{
public:
	GameSystem();
	~GameSystem();
	void  Update();
	void Render();
	void Load();
	void FloodFill(int x, int y, int n, int m);
	void SetProperty();
	void MakeEdge();

	Player* player = new Player();
	
	LPDIRECT3DTEXTURE9* backgroundTex;
	LPDIRECT3DTEXTURE9* maskTex;
	LPDIRECT3DTEXTURE9* dotTex;
	//LPDIRECT3DTEXTURE9 backgroundTex;
	LPD3DXSPRITE spr;
};

