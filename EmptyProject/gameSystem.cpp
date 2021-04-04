#include "DXUT.h"
#include "gameSystem.h"
#include "global.h"
#include <stack>

using namespace std;

GameSystem::GameSystem()
{
	Load();
	player->px = WIDTH-1;
	player->py = 0;
	player->playerState = player->ON_EDGE;

	//map초기화
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
	for (int y = 0; y <HEIGHT; ++y)
	{
		map[y * WIDTH + 0] = MAP_PROPERTY_EDGE;
		map[y * WIDTH + (WIDTH-1)] = MAP_PROPERTY_EDGE;
		binaryMap[y * WIDTH + 0] = MAP_PROPERTY_VISIT;
		binaryMap[y * WIDTH + (WIDTH-1)] = MAP_PROPERTY_VISIT;
	}
	for (int x = 0; x < WIDTH; ++x)
	{
		map[0 * WIDTH + x] = MAP_PROPERTY_EDGE;
		map[(HEIGHT-1) * WIDTH + x] = MAP_PROPERTY_EDGE;
		binaryMap[0 * WIDTH + x] = MAP_PROPERTY_VISIT;
		binaryMap[(HEIGHT-1) * WIDTH + x] = MAP_PROPERTY_VISIT;
	}

	
}

void GameSystem::Update()
{
	if (player->makeVisit)
	{
		SetProperty();
	}

	player->Update();
	//enemy->Update();
}

void GameSystem::MakeEdge()
{
	for (int x = 0; x < WIDTH; ++x)
	{
		for (int y = 0; y < HEIGHT; ++y)
		{
			if (map[y * WIDTH + x] == MAP_PROPERTY_VISIT)
			{
				if (
					map[(y - 1) * WIDTH + x] == MAP_PROPERTY_EMPTY ||
					map[(y + 1) * WIDTH + x] == MAP_PROPERTY_EMPTY ||
					map[y * WIDTH + (x - 1)] == MAP_PROPERTY_EMPTY ||
					map[y * WIDTH + (x + 1)] == MAP_PROPERTY_EMPTY ||
					map[(y - 1) * WIDTH + (x - 1)] == MAP_PROPERTY_EMPTY ||
					map[(y - 1) * WIDTH + (x + 1)] == MAP_PROPERTY_EMPTY ||
					map[(y + 1) * WIDTH + (x - 1)] == MAP_PROPERTY_EMPTY ||
					map[(y + 1) * WIDTH + (x + 1)] == MAP_PROPERTY_EMPTY)
				{
					map[y * WIDTH + x] = MAP_PROPERTY_EDGE;
				}
			}
		}
	}
}
void GameSystem::SetProperty()
{
	FloodFill(enemy->getPos().x, enemy->getPos().y, MAP_PROPERTY_EMPTY, MAP_PROPERTY_TEMP);

	for (int i = 0; i < WIDTH * HEIGHT; ++i)
	{
		if (map[i] == MAP_PROPERTY_TEMP)
		{
			binaryMap[i] = MAP_PROPERTY_EMPTY;
		}
		else
		{
			binaryMap[i] = MAP_PROPERTY_VISIT;
		}
	}
	memcpy(map, binaryMap, WIDTH * HEIGHT * sizeof(int));

	RECT tdr = { 0,0,WIDTH,HEIGHT };
	D3DLOCKED_RECT tlr;
	if (SUCCEEDED((*maskTex)->LockRect(0, &tlr, &tdr, 0)))
	{
		DWORD* p = (DWORD*)tlr.pBits;
		for (int i = 0; i < WIDTH * HEIGHT; ++i)
		{
;
			if (map[i] == MAP_PROPERTY_VISIT)
			{
				p[i] = mapData1[i];
				//p[i] = D3DCOLOR_ARGB(255, 255, 0, 0);
			}
		}	
		(*maskTex)->UnlockRect(0);
	}
	player->visitingPos.clear();
	MakeEdge();
	player->makeVisit = false;
}
void GameSystem::FloodFill(int x, int y, int n, int m)
{
	stack<int> posStack;
	posStack.push(y*WIDTH+x);
	while (!posStack.empty())
	{
		int pos = posStack.top();
		posStack.pop();

		int nx = pos % WIDTH;
		int ny = pos / WIDTH;

		if (nx < 0)continue;
		if (nx >= WIDTH)continue;
		if (ny < 0)continue;
		if (ny >= HEIGHT)continue;

		if (map[pos] != n) continue;
		map[pos] = m;

		posStack.push((ny - 1) * WIDTH + nx);
		posStack.push((ny + 1) * WIDTH + nx);
		posStack.push(ny * WIDTH + (nx + 1));
		posStack.push(ny * WIDTH + (nx-1));

	}
}
void GameSystem::Load()
{
	D3DXCreateSprite(DXUTGetD3D9Device(), &spr);

	backgroundTex = new LPDIRECT3DTEXTURE9();
	D3DXCreateTextureFromFileExA(
		DXUTGetD3D9Device(),
		"img/background.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		0, 
		0,
		D3DFMT_UNKNOWN, 
		D3DPOOL_MANAGED,
		D3DX_DEFAULT, 
		D3DX_DEFAULT,
		0,
		nullptr,
		nullptr, 
		backgroundTex);

	maskTex = new LPDIRECT3DTEXTURE9();
	D3DXCreateTextureFromFileExA(
		DXUTGetD3D9Device(), 
		"img/mask.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		0,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0,
		nullptr, 
		nullptr, 
		maskTex);

	dotTex = new LPDIRECT3DTEXTURE9();
	D3DXCreateTextureFromFileExA(DXUTGetD3D9Device(), "img/dot.png", D3DX_DEFAULT, D3DX_DEFAULT, 0, 0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0,
		nullptr, nullptr, dotTex);

	//mapData만들기
	//mapData = new DWORD[WIDTH * WIDTH];
	//RECT tdr = { 0,0,WIDTH,HEIGHT };
	//D3DLOCKED_RECT tlr;
	//if (SUCCEEDED((*backgroundTex)->LockRect(0, &tlr, &tdr, 0)))
	//{
	//	memcpy(mapData, (DWORD*)tlr.pBits, WIDTH * HEIGHT * sizeof(DWORD));
	//	(*backgroundTex)->UnlockRect(0);
	//}

	D3DLOCKED_RECT lr;
	RECT rt = { 0, 0,  WIDTH, HEIGHT };
	if (SUCCEEDED((*backgroundTex)->LockRect(0, &lr, &rt, 0)))
	{
		DWORD* p = (DWORD*)lr.pBits;
		for (int i = 0; i < WIDTH * HEIGHT; ++i)
		{
			mapData1[i] = p[i];
		}
		//memcpy(mapData1, p, WIDTH * HEIGHT * sizeof(int));
		(*backgroundTex)->UnlockRect(0);
	}
}
GameSystem::~GameSystem()
{
	delete player;
	delete enemy;
	spr->Release();
	(*backgroundTex)->Release();
	(*maskTex)->Release();
	(*dotTex)->Release();
}
void GameSystem::Render()
{
	D3DXVECTOR3 pos(STARTX_POINT, STARTY_POINT, 0);

	/*mask*/
	spr->Begin(D3DXSPRITE_ALPHABLEND);
	spr->Draw(*maskTex, 0, 0, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));
	spr->End();


	spr->Begin(D3DXSPRITE_ALPHABLEND);
	for (int i = 0; i < player->visitingPos.size(); ++i)
	{
		int px = player->visitingPos[i].x;
		int py = player->visitingPos[i].y;
		D3DXVECTOR3 pos(STARTX_POINT + px, STARTY_POINT + py, 0);
		spr->Draw(*dotTex, 0, 0, &pos, D3DCOLOR_ARGB(255, 255, 0, 0));
	}
	for (int y = 0; y < HEIGHT; ++y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{
			if (map[y*WIDTH+x] == MAP_PROPERTY_EDGE)
			{
				D3DXVECTOR3 pos(STARTX_POINT + x, STARTY_POINT + y, 0);
				spr->Draw(*dotTex, 0, 0, &pos, D3DCOLOR_ARGB(255, 0, 0, 0));
			}
		}
	}
	spr->End();

	player->Render();
	enemy->Render();
}
