#include "ColliderTestScene.h"
#include <memory>
#include "BoxCollider.h"
#include "CircleCollider.h"
#include <DxLib.h>
#include "game.h"
#include "Time.h"
#include "Input.h"
#include "TestScene.h"
#include "SceneController.h"

void ColliderTestScene::HitKansuu()
{
	Input& input = Input::GetInstance();
	Vector2* pVec = nowMousePos;
	std::shared_ptr<Collider> pCol;
	bool atatta = false;
	color = 0xffffff;
	for (const auto& col : colArray)
	{
		if (nowCol == col) continue;

		if (nowCol->CheckHit(*col))
		{
			printf("��������");
			atatta = true;
			pVec = col->GetPVec();
			pCol = col;
			color = 0xff0000;
		}
	}

	if (input.IsTrigger(PAD_INPUT_1) && atatta)
	{
		nowMousePos = pVec;
		nowCol = pCol;
	}
}

ColliderTestScene::ColliderTestScene() :
	m_frameCount(0),
	color(0xffffff)
{
	boxCol = std::make_shared<BoxCollider>(boxPos, boxHava.x, boxHava.y);
	circleCol = std::make_shared<CircleCollider>(circlePos, 32);
	circleCol2 = std::make_shared<CircleCollider>(circlePos2, 32);
	boxCol2 = std::make_shared<BoxCollider>(boxPos2, boxHava.x, boxHava.y);
	nowCol = circleCol;
	nowMousePos = &circlePos;
	colArray[0] = circleCol;
	colArray[1] = boxCol;
	colArray[2] = circleCol2;
	colArray[3] = boxCol2;
}

ColliderTestScene::~ColliderTestScene()
{
}

void ColliderTestScene::Update()
{
	Input& input = Input::GetInstance();
	//boxPos.x++;
	// �~�̓}�E�X�ɉ����Ĉړ�
	int mouseX, mouseY;
	GetMousePoint(&mouseX, &mouseY);
	nowMousePos->x = mouseX;
	nowMousePos->y = mouseY;
	HitKansuu();

	if (input.IsTrigger(PAD_INPUT_2))
	{
		SceneController::GetInstance().ChangeScene(std::make_shared<TestScene>());
		return;
	}
}

void ColliderTestScene::Draw()
{
	DrawFormatString(0, 0, color, "FPS=%f", Time::GetInstance().FPS());
	DrawString(0, 15, "ColliderTestScene", color);
	Vector2 nya = boxCol->GetPos();
	DrawFormatString(0, 30, color, "�R���C�_�[�����Ă�Box1�̈�x%f:y%f", nya.x, nya.y);
	Vector2 nyai = circleCol->GetPos();
	DrawFormatString(0, 45, color, "�R���C�_�[�����Ă�Circle1�̈ʒux%f:y%f", nyai.x, nyai.y);
	DrawCircle(circlePos.x, circlePos.y, 32, color);
	DrawBox(boxPos.x - boxHava.x * 0.5f, boxPos.y - boxHava.y * 0.5f, boxPos.x + boxHava.x * 0.5f, boxPos.y + boxHava.y * 0.5f, color, true);
	DrawCircle(circlePos2.x, circlePos2.y, 32, color);
	DrawBox(boxPos2.x - boxHava.x * 0.5f, boxPos2.y - boxHava.y * 0.5f, boxPos2.x + boxHava.x * 0.5f, boxPos2.y + boxHava.y * 0.5f, color, true);
}
