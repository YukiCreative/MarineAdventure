#pragma once
#include "Door.h"

class DoorGameClear : public Door
{
private:
	void Entry() override;
public:
	DoorGameClear(Player& player, Camera& camera, const Vector2& initPos);
};

