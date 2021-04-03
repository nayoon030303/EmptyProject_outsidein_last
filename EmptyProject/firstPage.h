#pragma once
#include "page.h"
#include "DXUT.h"

class FirstPage:public Page
{
public:
	FirstPage();
	virtual~FirstPage();
	void Render()override;
	void Update()override;


	LPDIRECT3DTEXTURE9* backgroundTex;
	LPDIRECT3DTEXTURE9* maskTex;
	//LPDIRECT3DTEXTURE9 backgroundTex;

	LPD3DXSPRITE spr;
};

