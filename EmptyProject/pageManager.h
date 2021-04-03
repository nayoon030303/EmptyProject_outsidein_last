#pragma once
#include "DXUT.h"


class Page;

class PageManager
{
public:
	virtual~PageManager();
	void MakeTitlePage();
	void MakeFirstGamePage();
	void MakeSecondGamePage();

	void Render();
	void Update();

	Page* currentPage;
	Page* prevPage;
	
};
