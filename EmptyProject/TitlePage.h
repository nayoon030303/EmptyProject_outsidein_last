#pragma once
#include "page.h"

class TitlePage:public Page
{
public:
	TitlePage();
	virtual~TitlePage();
	void Render()override;
	void Update()override;

	LPDIRECT3DTEXTURE9* backgroundTex;
	LPD3DXSPRITE sprite;
};

