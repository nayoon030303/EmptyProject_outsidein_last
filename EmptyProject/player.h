#pragma once
#include "DXUT.h"
#include <vector>

using namespace std;

class Player
{
public:
	Player();
	~Player();
	void Render();
	void Update();
	void CanVisiting();
	void CanEdge();

	enum  PlayerState
	{
		ON_EDGE,
		VISITING
	};
	PlayerState playerState;
	int px, py;
	LPDIRECT3DTEXTURE9* playerTex;
	LPD3DXSPRITE sprite;
	vector<D3DXVECTOR2> visitingPos;
	D3DXVECTOR2 startPos;
	bool press;
	bool makeVisit;
	int nextMap;
	int speed;

	D3DXVECTOR2 getPos()
	{
		return D3DXVECTOR2(px, py);
	}
};

