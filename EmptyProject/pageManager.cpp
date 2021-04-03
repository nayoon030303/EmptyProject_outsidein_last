#include "pageManager.h"
#include "DXUT.h"
#include "page.h"
#include "global.h"
#include "TitlePage.h"

void PageManager::MakeTitlePage()
{
	if (currentPage != nullptr)
	{
		if (currentPage->classType == FIRST_PAGE)
		{
			
		}
		delete currentPage;
	}
	TitlePage* titlePage = new TitlePage();
	currentPage = titlePage;
}

void PageManager::MakeFirstGamePage()
{

}

void PageManager::MakeSecondGamePage()
{

}

void PageManager::Render()
{
	if (currentPage != nullptr)
	{
		currentPage->Render();
	}
}
void PageManager::Update()
{
	if (currentPage != nullptr)
	{
		currentPage->Update();
	}
}

PageManager::~PageManager()
{
	if (currentPage != nullptr)
	{
		delete currentPage;
	}
}