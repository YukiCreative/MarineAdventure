#include "DoorStage2ToStage3.h"
#include "SceneGame.h"
#include "SceneController.h"
#include <cassert>

namespace
{
	const std::string kMapPath = "Data/MapData/Stage3.fmf";
	const Vector2 kNextPlayerPos = { 80 * (4 - 8), 80 * (125 - 5) };
}

void DoorStage2ToStage3::Entry()
{
	// BGM�ς�����
}

void DoorStage2ToStage3::In()
{
	// �Q�[���V�[���Ɏw�����o��
	std::shared_ptr<SceneGame> gameScene = std::dynamic_pointer_cast<SceneGame>(SceneController::GetInstance().CurrentScene());
	assert(gameScene && "�_�E���L���X�g�Ɏ��s");

	Entry();

	gameScene->ChangeMapWithFadeOut(m_path, m_nextPlayerPos);
}

DoorStage2ToStage3::DoorStage2ToStage3(Player& player, Camera& camera, const Vector2& initPos) :
	Door(player, camera, initPos, kMapPath, kNextPlayerPos)
{
}
