#include "DoorStageClear.h"
#include "SceneController.h"

namespace
{
	// すぐクリア画面に行くのでマップはどれでもいい
	// でもドアに入ったときが地上なので地上に出るようにする
	const std::string kMapPath = "Data/MapData/Stage2";
	const Vector2 kNextPlayerPos = { 80 * (5 - 8), 80 * (35 - 5) };
}

void DoorGameClear::Entry()
{
	// すぐにシーン遷移
	SceneController::GetInstance().ChangeScene("Clear");
}

DoorGameClear::DoorGameClear(Player& player, Camera& camera, const Vector2& initPos) :
	Door(player, camera, initPos, kMapPath, kNextPlayerPos)
{
}
