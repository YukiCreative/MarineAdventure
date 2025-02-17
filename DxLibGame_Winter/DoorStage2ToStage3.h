#pragma once
#include "Door.h"

class DoorStage2ToStage3 : public Door
{
private:
	void Entry() override;
	void In() override;
public:
	DoorStage2ToStage3(Player& player, Camera& camera, const Vector2& initPos);
};

