#pragma once
#include "Door.h"

class DoorStage1ToStage2 : public Door
{
private:
	void Entry() override;
	void In() override;
public:
	DoorStage1ToStage2(Player& player, Camera& camera, const Vector2& initPos);
};

