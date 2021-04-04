#include "DXUT.h"
#include "player.h"
#include "global.h"
#include <vector>

Player::Player()
{

	playerState = ON_EDGE;
	makeVisit = false;
	speed = 3;
	D3DXCreateSprite(DXUTGetD3D9Device(), &sprite);
	playerTex = new LPDIRECT3DTEXTURE9();
	D3DXCreateTextureFromFileExA(
		DXUTGetD3D9Device(), 
		"img/player.png", 
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
		playerTex);
	
}

void Player:: Render()
{
	
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	D3DXVECTOR3 pos(STARTX_POINT+px-5, STARTY_POINT+py-5, 0);
	sprite->Draw(*playerTex, nullptr, nullptr, &pos, D3DCOLOR_ARGB(255, 0, 255, 0));
	sprite->End();
}

void Player::Update()
{
	if (px < 0)
	{
		px = 0;
	}
	if (px >= WIDTH)
	{
		px = WIDTH-1;
	}
	if (py < 0)
	{
		py = 0;
	}
	if (py >= HEIGHT)
	{
		py = HEIGHT-1;
	}


	//control
	if ((GetAsyncKeyState(VK_CONTROL) & 0x8000) != 0)
	{
		press = true;
	}
	else
	{
		if (playerState == VISITING)
		{
			press = false;
			px = startPos.x;
			py = startPos.y;
			playerState = ON_EDGE;
			for (int i = 0; i < visitingPos.size(); ++i)
			{
				int nx = visitingPos[i].x;
				int ny = visitingPos[i].y;
				map[ny * WIDTH + nx] = MAP_PROPERTY_EMPTY;
			}
			visitingPos.clear();
		}
	}

	//right
	if((GetAsyncKeyState(VK_RIGHT) & 0x8000) != 0 && px+1<WIDTH)
	{
		startPos.x = px;
		startPos.y = py;
		for (int i = 0; i < speed; ++i)
		{
			int nextX = px + 1;
			int nextY = py;
			int nextProperty = map[nextY * WIDTH + nextX];

			if (map[py * WIDTH + px] == MAP_PROPERTY_EDGE &&
				nextProperty == MAP_PROPERTY_EDGE  )
			{
				px = nextX;
				py = nextY;
			}
			if (map[py * WIDTH + px] == MAP_PROPERTY_EDGE &&
				nextProperty == MAP_PROPERTY_EMPTY && press)
			{				
				px = nextX;
				py = nextY;
				map[py * WIDTH + px] = MAP_PROPERTY_VISITING;
				visitingPos.push_back(D3DXVECTOR2(px, py));
				playerState = VISITING;
				//CanVisiting();
			}
			if (map[py * WIDTH + px] == MAP_PROPERTY_VISITING &&
				nextProperty == MAP_PROPERTY_EMPTY && press)
			{
				px = nextX;
				py = nextY;
				map[py * WIDTH + px] = MAP_PROPERTY_VISITING;
				visitingPos.push_back(D3DXVECTOR2(px, py));
				playerState = VISITING;
				//CanVisiting();
			}
			if (map[py * WIDTH + px] == MAP_PROPERTY_VISITING &&
				nextProperty == MAP_PROPERTY_EDGE && press)
			{
				px = nextX;
				py = nextY;
				playerState = ON_EDGE;
				makeVisit = true;
				press = false;
				//CanVisiting();
			}
		}
	}
	//left
	else if ((GetAsyncKeyState(VK_LEFT) & 0x8000) != 0)
	{
		startPos.x = px;
		startPos.y = py;
		for (int i = 0; i < speed; ++i)
		{
			int nextX = px - 1;
			int nextY = py;
			int nextProperty = map[nextY * WIDTH + nextX];

			if (map[py * WIDTH + px] == MAP_PROPERTY_EDGE &&
				nextProperty == MAP_PROPERTY_EDGE)
			{
				px = nextX;
				py = nextY;
			}
			if (map[py * WIDTH + px] == MAP_PROPERTY_EDGE &&
				nextProperty == MAP_PROPERTY_EMPTY && press)
			{
				px = nextX;
				py = nextY;
				map[py * WIDTH + px] = MAP_PROPERTY_VISITING;
				visitingPos.push_back(D3DXVECTOR2(px, py));
				playerState = VISITING;
				//CanVisiting();
			}
			if (map[py * WIDTH + px] == MAP_PROPERTY_VISITING &&
				nextProperty == MAP_PROPERTY_EMPTY && press)
			{
				px = nextX;
				py = nextY;
				map[py * WIDTH + px] = MAP_PROPERTY_VISITING;
				visitingPos.push_back(D3DXVECTOR2(px, py));
				playerState = VISITING;
				//CanVisiting();
			}
			if (map[py * WIDTH + px] == MAP_PROPERTY_VISITING &&
				nextProperty == MAP_PROPERTY_EDGE && press)
			{
				px = nextX;
				py = nextY;
				playerState = ON_EDGE;
				makeVisit = true;
				press = false;
				//CanVisiting();
			}
		}
	}
	//up
	else if ((GetAsyncKeyState(VK_UP) & 0x8000) != 0)
	{
		startPos.x = px;
		startPos.y = py;
		for (int i = 0; i < speed; ++i)
		{
			int nextX = px;
			int nextY = py - 1;
			int nextProperty = map[nextY * WIDTH + nextX];

			if (map[py * WIDTH + px] == MAP_PROPERTY_EDGE &&
				nextProperty == MAP_PROPERTY_EDGE)
			{
				px = nextX;
				py = nextY;
			}
			if (map[py * WIDTH + px] == MAP_PROPERTY_EDGE &&
				nextProperty == MAP_PROPERTY_EMPTY && press)
			{
				px = nextX;
				py = nextY;
				map[py * WIDTH + px] = MAP_PROPERTY_VISITING;
				visitingPos.push_back(D3DXVECTOR2(px, py));
				playerState = VISITING;
				//CanVisiting();
			}
			if (map[py * WIDTH + px] == MAP_PROPERTY_VISITING &&
				nextProperty == MAP_PROPERTY_EMPTY && press)
			{
				px = nextX;
				py = nextY;
				map[py * WIDTH + px] = MAP_PROPERTY_VISITING;
				visitingPos.push_back(D3DXVECTOR2(px, py));
				playerState = VISITING;
				//CanVisiting();
			}
			if (map[py * WIDTH + px] == MAP_PROPERTY_VISITING &&
				nextProperty == MAP_PROPERTY_EDGE && press)
			{
				px = nextX;
				py = nextY;
				playerState = ON_EDGE;
				makeVisit = true;
				press = false;
				//CanVisiting();
			}
		}
	}
	//down
	else if ((GetAsyncKeyState(VK_DOWN) & 0x8000) != 0)
	{
		startPos.x = px;
		startPos.y = py;
		for (int i = 0; i < speed; ++i)
		{
			int nextX = px;
			int nextY = py + 1;
			int nextProperty = map[nextY * WIDTH + nextX];
			if (map[py * WIDTH + px] == MAP_PROPERTY_EDGE)
			{
				int a = 0;
			}
			if (map[py * WIDTH + px] == MAP_PROPERTY_EDGE &&
				nextProperty == MAP_PROPERTY_EDGE)
			{
				px = nextX;
				py = nextY;
			}
			if (map[py * WIDTH + px] == MAP_PROPERTY_EDGE &&
				nextProperty == MAP_PROPERTY_EMPTY && press)
			{
				px = nextX;
				py = nextY;
				map[py * WIDTH + px] = MAP_PROPERTY_VISITING;
				visitingPos.push_back(D3DXVECTOR2(px, py));
				playerState = VISITING;
				//CanVisiting();
			}
			if (map[py * WIDTH + px] == MAP_PROPERTY_VISITING &&
				nextProperty == MAP_PROPERTY_EMPTY && press)
			{
				px = nextX;
				py = nextY;
				map[py * WIDTH + px] = MAP_PROPERTY_VISITING;
				visitingPos.push_back(D3DXVECTOR2(px, py));
				playerState = VISITING;
				//CanVisiting();
			}
			if (map[py * WIDTH + px] == MAP_PROPERTY_VISITING &&
				nextProperty == MAP_PROPERTY_EDGE && press)
			{
				px = nextX;
				py = nextY;
				playerState = ON_EDGE;
				makeVisit = true;
				press = false;
				//CanVisiting();
			}
		}
	}
	press = false;

	//if (playerState == ON_EDGE)
	//{

	//	if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) != 0)
	//	{
	//		nextMap = map[py * WIDTH + (px + 1)];
	//		CanVisiting();
	//		if (nextMap == MAP_PROPERTY_EDGE)
	//		{
	//			px += speed;
	//		}
	//		
	//	}
	//	else if ((GetAsyncKeyState(VK_LEFT) & 0x8000) != 0)
	//	{
	//		nextMap = map[py * WIDTH + (px - 1)];
	//		CanVisiting();
	//		if (nextMap == MAP_PROPERTY_EDGE)
	//		{
	//			px -= speed;
	//		}
	//	}
	//	else if ((GetAsyncKeyState(VK_UP) & 0x8000) != 0)
	//	{
	//		nextMap = map[(py - 1) * WIDTH + px];
	//		CanVisiting();
	//		if (nextMap == MAP_PROPERTY_EDGE)
	//		{
	//			py -= speed;
	//		}
	//	}
	//	else if ((GetAsyncKeyState(VK_DOWN) & 0x8000) != 0)
	//	{
	//		nextMap = map[(py + 1) * WIDTH + px];
	//		CanVisiting();
	//		if (nextMap == MAP_PROPERTY_EDGE)
	//		{
	//			py += speed;
	//		}
	//	}
	//}
	//else if (playerState == VISITING)
	//{

	//	if ((GetAsyncKeyState(VK_CONTROL) & 0x8000) == 0)
	//	{
	//		press = false;

	//		px = startPos.x;
	//		py = startPos.y;
	//		playerState = ON_EDGE;
	//		for (int i = 0; i < visitingPos.size(); ++i)
	//		{
	//			int nx = visitingPos[i].x;
	//			int ny = visitingPos[i].y;
	//			//map[ny * WIDTH + nx] = MAP_PROPERTY_EMPTY;
	//		}
	//		//visitingPos.clear();
	//	}

	//	else if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) != 0)
	//	{
	//		nextMap = map[py * WIDTH + (px + 1)];
	//		if (nextMap == MAP_PROPERTY_EMPTY)
	//		{		
	//			for (int i = 0; i <speed; ++i)
	//			{
	//				px += 1;
	//				map[py * WIDTH + px] = MAP_PROPERTY_VISITING;
	//				visitingPos.push_back(D3DXVECTOR2(px, py));
	//			}
	//			
	//		}
	//		
	//		CanEdge();
	//	}
	//	else if ((GetAsyncKeyState(VK_LEFT) & 0x8000) != 0)
	//	{
	//		nextMap = map[py * WIDTH + (px - 1)];
	//		if (nextMap == MAP_PROPERTY_EMPTY)
	//		{
	//			px -= speed;
	//		}
	//		CanEdge();
	//	}
	//	else if ((GetAsyncKeyState(VK_UP) & 0x8000) != 0)
	//	{
	//		nextMap = map[(py - 1) * WIDTH + px];
	//		if (nextMap == MAP_PROPERTY_EMPTY)
	//		{
	//			for (int i = 0; i < speed; ++i)
	//			{
	//				if(map[(py-1)*WIDTH+px] != MAP_PROPERTY_EDGE)
	//					py -= 1;					
	//				map[py * WIDTH + px] = MAP_PROPERTY_VISITING;
	//				visitingPos.push_back(D3DXVECTOR2(px, py));
	//			}
	//		}
	//		
	//		CanEdge();
	//	}
	//	else if ((GetAsyncKeyState(VK_DOWN) & 0x8000) != 0)
	//	{
	//		nextMap = map[(py + 1) * WIDTH + px];
	//		if (nextMap == MAP_PROPERTY_EMPTY)
	//		{
	//			py += speed;
	//		}
	//		CanEdge();
	//	}
	//}
	
}

void Player::CanEdge()
{
	if (nextMap == MAP_PROPERTY_EDGE)
	{
		playerState = ON_EDGE;
		makeVisit = true;
		press = false;
	}
}

void Player::CanVisiting()
{
	map[py * WIDTH + px] = MAP_PROPERTY_VISITING;
	visitingPos.push_back(D3DXVECTOR2(px, py));
	playerState = VISITING;
	
	
}

Player::~Player()
{
	sprite->Release();
	(*playerTex)->Release();
}