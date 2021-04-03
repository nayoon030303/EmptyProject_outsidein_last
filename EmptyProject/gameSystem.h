#pragma once
#include "DXUT.h"

class GameSystem
{
public:
	GameSystem();
	void  Update();
	void Render();
	void Load();

	LPDIRECT3DTEXTURE9* backgroundTex;
	LPDIRECT3DTEXTURE9* maskTex;
	LPDIRECT3DTEXTURE9* dotTex;
	//LPDIRECT3DTEXTURE9 backgroundTex;

	LPD3DXSPRITE spr;
};

