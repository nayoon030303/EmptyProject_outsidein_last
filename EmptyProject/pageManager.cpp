#include "pageManager.h"
#include "DXUT.h"
#include "page.h"
#include "global.h"
#include "TitlePage.h"
#include "firstPage.h"

void PageManager::MakeTitlePage()
{
	if (currentPage != nullptr)
	{
		if (currentPage->classType == FIRST_PAGE)
		{
			
		}
		delete currentPage;
	}
	TitlePage* newPage = new TitlePage();
	currentPage = newPage;
}

void PageManager::MakeFirstGamePage()
{
	if (currentPage != nullptr)
	{
		if (currentPage->classType == FIRST_PAGE)
		{

		}
		delete currentPage;
	}
	FirstPage* newPage = new FirstPage();
	currentPage = newPage;
}

void PageManager::MakeSecondGamePage()
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
void PageManager::deleteCurrent()
{
	if (currentPage != nullptr)
	{
		delete currentPage;
	}
}
