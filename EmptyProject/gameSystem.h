#pragma once
#include "DXUT.h"
#include "player.h"



class GameSystem
{
public:
	GameSystem();
	void  Update();
	void Render();
	void Load();

	Player* player = new Player();

	LPDIRECT3DTEXTURE9* backgroundTex;
	LPDIRECT3DTEXTURE9* maskTex;
	LPDIRECT3DTEXTURE9* dotTex;
	//LPDIRECT3DTEXTURE9 backgroundTex;
	LPD3DXSPRITE spr;
};
