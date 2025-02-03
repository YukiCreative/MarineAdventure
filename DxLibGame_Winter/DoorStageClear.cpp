#include "DoorStageClear.h"
#include "SceneController.h"
#include "SceneGame.h"
#include <cassert>

namespace
{
	// すぐクリア画面に行くのでマップはどれでもいい
	// でもドアに入ったときが地上なので地上に出るようにする
	const std::string kMapPath = "Data/MapData/Stage2";
	const Vector2 kNextPlayerPos = { 80 * (5 - 8), 80 * (35 - 5) };
}

void DoorGameClear::Entry()
{
	// この関数いらんやん
}

void DoorGameClear::In()
{
	// ゲームシーンに指示を出す
	std::shared_ptr<SceneGame> gameScene = std::dynamic_pointer_cast<SceneGame>(SceneController::GetInstance().CurrentScene());
	assert(gameScene && "ダウンキャストに失敗");

	gameScene->GameClear();
}

DoorGameClear::DoorGameClear(Player& player, Camera& camera, const Vector2& initPos) :
	Door(player, camera, initPos, kMapPath, kNextPlayerPos)
{
}
