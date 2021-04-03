#pragma once
#include "DXUT.h"
class Player
{
public:
	Player();
	~Player();
	void Render();
	void Update();

	int px, py;
	LPDIRECT3DTEXTURE9* playerTex;
	LPD3DXSPRITE sprite;
	
	D3DXVECTOR2 getPos()
	{
		return D3DXVECTOR2(px, py);
	}
};

