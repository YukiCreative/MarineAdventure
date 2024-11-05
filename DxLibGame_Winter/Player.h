#pragma once
#include "Vector2.h"

class Player
{
private:
	Vector2 m_pos;
public:
	Player();

	void Update();
	void Draw();
};

