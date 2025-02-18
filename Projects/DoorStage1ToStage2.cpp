#include "DoorStage1ToStage2.h"
#include "SceneGame.h"
#include "SceneController.h"
#include <cassert>

namespace
{
	const std::string kMapPath = "Data/MapData/Stage2.fmf";
	const Vector2 kNextPlayerPos = { 80 * (2 - 8), 80 * (8 - 5) };
}

void DoorStage1ToStage2::Entry()
{
	
}

void DoorStage1ToStage2::In()
{
	// ゲームシーンに指示を出す
	std::shared_ptr<SceneGame> gameScene = std::dynamic_pointer_cast<SceneGame>(SceneController::GetInstance().CurrentScene());
	assert(gameScene && "ダウンキャストに失敗");

	Entry();

	gameScene->ChangeMapWithFadeOut(Stages::kStage2, m_path, m_nextPlayerPos);
}

DoorStage1ToStage2::DoorStage1ToStage2(Player& player, Camera& camera, const Vector2& initPos) :
	Door(player, camera, initPos, kMapPath, kNextPlayerPos)
{
}
