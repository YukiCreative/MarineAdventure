#include "DoorStage2ToStage3.h"

namespace
{
	const std::string kMapPath = "Data/MapData/Stage3.fmf";
	const Vector2 kNextPlayerPos = { 80 * (4 - 8), 80 * (125 - 5) };
}

void DoorStage2ToStage3::Entry()
{
	// BGM•Ï‚¦‚½‚¢
}

DoorStage2ToStage3::DoorStage2ToStage3(Player& player, Camera& camera, const Vector2& initPos) :
	Door(player, camera, initPos, kMapPath, kNextPlayerPos)
{
}
