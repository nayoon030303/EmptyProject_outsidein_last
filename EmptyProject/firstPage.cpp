#include "DXUT.h"
#include "firstPage.h"
#include "global.h"


FirstPage::FirstPage()
{
	
}
void FirstPage::Render()
{
	
	gameSystem.Render();

}

void FirstPage::Update()
{
	gameSystem.Update();
}

FirstPage::~FirstPage()
{
	(*gameSystem.backgroundTex)->Release();
	(*gameSystem.maskTex)->Release();
	(*gameSystem.dotTex)->Release();
	(gameSystem.spr)->Release();
	
}