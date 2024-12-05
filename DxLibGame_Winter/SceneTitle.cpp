#include "SceneTitle.h"
#include <DxLib.h>
#include "Input.h"
#include "SceneController.h"
#include <cassert>
#include "game.h"

#include "TestScene.h"

SceneTitle::SceneTitle()
{
	// �^�C�g���摜�����[�h
	m_titleHandle = LoadGraph("Data/Image/�C�w�i.jpg");
	assert(m_titleHandle != -1 && "�摜");
}

SceneTitle::~SceneTitle()
{
	DeleteGraph(m_titleHandle);
}

void SceneTitle::Update()
{
	Input& input = Input::GetInstance();
	if (input.IsPressed("ChangeScene_Debug"))
	{
		SceneController::GetInstance().ChangeScene(std::make_shared<TestScene>());
	}
}

void SceneTitle::Draw()
{
	DrawRotaGraph(Game::kScreenWidth * 0.5f, Game::kScreenHeight * 0.5f, 2.5, 0.0, m_titleHandle, false);
	DrawString(300, Game::kScreenHeight * 0.5f, "Title", 0x000000);
}
