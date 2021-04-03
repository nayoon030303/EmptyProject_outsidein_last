#pragma once
#include "DXUT.h"


class Page;

class PageManager
{
public:
	void MakeTitlePage();
	void MakeFirstGamePage();
	void MakeSecondGamePage();

	void Render();
	void Update();
	void deleteCurrent();

	Page* currentPage;
	Page* prevPage;
	
};
