#include "DoorStage1ToStage2.h"

namespace
{
	const std::string kMapPath = "Data/MapData/Stage2.fmf";
	const Vector2 kNextPlayerPos = { 80 * (2 - 8), 80 * (8 - 5) };
}

void DoorStage1ToStage2::Entry()
{
	// ‚±‚ê‚Í‰½‚à‚µ‚È‚¢
}

DoorStage1ToStage2::DoorStage1ToStage2(Player& player, Camera& camera, const Vector2& initPos) :
	Door(player, camera, initPos, kMapPath, kNextPlayerPos)
{
}
