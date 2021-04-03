#pragma once

class Page
{
public:
	virtual~Page() {};
	virtual void Render() = 0;
	virtual void Update() = 0;

	int classType;
};