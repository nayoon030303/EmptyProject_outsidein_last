#include "DXUT.h"
#include "gameSystem.h"
#include "global.h"


GameSystem::GameSystem()
{
	Load();
	player->px = 0;
	player->py =0;

	//map�ʱ�ȭ
	/*EMPTY*/
	for (int y = 0; y < HEIGHT; ++y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{
			map[y * WIDTH + x] = MAP_PROPERTY_EMPTY;
			binaryMap[y * WIDTH + x] = MAP_PROPERTY_EMPTY;
		}
	}
	/*EDGE*/
	for (int y = 2; y <HEIGHT-3; ++y)
	{
		map[y * WIDTH + 2] = MAP_PROPERTY_EDGE;
		map[y * WIDTH + (WIDTH-3)] = MAP_PROPERTY_EDGE;
		binaryMap[y * WIDTH + 1] = MAP_PROPERTY_EDGE;
		binaryMap[y * WIDTH + (WIDTH-1)] = MAP_PROPERTY_EDGE;
	}
	for (int x = 2; x < WIDTH-3; ++x)
	{
		map[2 * WIDTH + x] = MAP_PROPERTY_EDGE;
		map[(HEIGHT-3) * WIDTH + x] = MAP_PROPERTY_EDGE;
		binaryMap[1 * WIDTH + x] = MAP_PROPERTY_EDGE;
		binaryMap[(HEIGHT-1) * WIDTH + x] = MAP_PROPERTY_EDGE;
	}

	
}

void GameSystem::Update()
{
	player->Update();
}

void GameSystem::Render()
{
	D3DXVECTOR3 pos(STARTX_POINT, STARTY_POINT, 0);
	/*spr->Begin(D3DXSPRITE_ALPHABLEND);
	
	spr->Draw(*backgroundTex, 0, 0, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));
	spr->End();*/
	
	spr->Begin(D3DXSPRITE_ALPHABLEND);
	spr->Draw(*maskTex, 0, 0, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));
	spr->End();

	spr->Begin(D3DXSPRITE_ALPHABLEND);
	for (int y = 0; y < HEIGHT; ++y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{
			if (map[y * WIDTH + x] == MAP_PROPERTY_EDGE)
			{
				D3DXVECTOR3 pos(STARTX_POINT + x, STARTY_POINT + y , 0);
				spr->Draw(*dotTex, 0, 0, &pos, D3DCOLOR_ARGB(255, 0, 0, 0));
			}
		}
	}
	spr->End();

	player->Render();

}

void GameSystem::Load()
{
	D3DXCreateSprite(DXUTGetD3D9Device(), &spr);

	backgroundTex = new LPDIRECT3DTEXTURE9();
	D3DXCreateTextureFromFileExA(DXUTGetD3D9Device(), "img/background.png",
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 0, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT,
		0,
		nullptr, nullptr, backgroundTex);

	maskTex = new LPDIRECT3DTEXTURE9();
	D3DXCreateTextureFromFileExA(DXUTGetD3D9Device(), "img/mask.png",
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 0, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT,
		0,
		nullptr, nullptr, maskTex);

	dotTex = new LPDIRECT3DTEXTURE9();
	D3DXCreateTextureFromFileExA(DXUTGetD3D9Device(), "img/dot.png", D3DX_DEFAULT, D3DX_DEFAULT, 0, 0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0,
		nullptr, nullptr, dotTex);

	RECT tdr = { 0,0,WIDTH,HEIGHT };
	D3DLOCKED_RECT tlr;
	if ((*backgroundTex) != nullptr)
	{
		if (SUCCEEDED((*backgroundTex)->LockRect(0, &tlr, &tdr, 0)))
		{
			DWORD* p = (DWORD*)tlr.pBits;
			memcpy(mapData, p, WIDTH * HEIGHT * 4);
			(*backgroundTex)->UnlockRect(0);
		}
	}

}

GameSystem::~GameSystem()
{
	delete player;
	spr->Release();
	(*backgroundTex)->Release();
	(*maskTex)->Release();
	(*dotTex)->Release();
}