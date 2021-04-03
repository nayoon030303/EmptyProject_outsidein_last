#include "DXUT.h"
#include "TitlePage.h"
#include "global.h"

TitlePage::TitlePage()
{
    D3DXCreateSprite(DXUTGetD3D9Device(), &sprite);

    backgroundTex = new LPDIRECT3DTEXTURE9();
    D3DXCreateTextureFromFileExA(DXUTGetD3D9Device(), "img/background.png", D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 0,
        0,
        D3DFMT_UNKNOWN,
        D3DPOOL_MANAGED,
        D3DX_DEFAULT,
        D3DX_DEFAULT,
        0,
        nullptr, nullptr, backgroundTex);
    
}

TitlePage::~TitlePage()
{
    sprite->Release();
    (*backgroundTex)->Release();
}

void TitlePage::Render()
{
   
    sprite->Begin(D3DXSPRITE_ALPHABLEND);
    D3DXVECTOR3 pos(STARTX_POINT-601/2, STARTY_POINT,0);
    sprite->Draw(*backgroundTex, nullptr, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));
    sprite->End();
}

void TitlePage::Update()
{
    if ((GetAsyncKeyState(VK_SPACE) * 0x8000) != 0)
    {
        pageManager.MakeFirstGamePage();
    }

}