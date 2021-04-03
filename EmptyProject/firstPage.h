#pragma once
#include "page.h"
#include "DXUT.h"
#include "gameSystem.h"

class FirstPage:public Page
{
public:
	FirstPage();
	virtual~FirstPage();
	void Render()override;
	void Update()override;

	GameSystem gameSystem;
	
};

