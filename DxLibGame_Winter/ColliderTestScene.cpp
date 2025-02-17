#include "ColliderTestScene.h"
#include <memory>
#include "BoxCollider.h"
#include "CircleCollider.h"
#include <DxLib.h>
#include "game.h"
#include "Time.h"
#include "Input.h"
#include "SceneGame.h"
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

		CollisionStatus result = nowCol->CheckHit(*col);
		if (result.isCollide)
		{
			printf("��������");
			atatta = true;
			pVec = col->GetPVec();
			pCol = col;
			color = 0xff0000;
			overLap = result.overlap;
		}
	}

	if (input.IsTrigger("Dash") && atatta)
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
	circleCol = std::make_shared<CircleCollider>(circlePos, 32.0f);
	circleCol2 = std::make_shared<CircleCollider>(circlePos2, 32.0f);
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

void ColliderTestScene::NormalUpdate()
{
	Input& input = Input::GetInstance();
	//boxPos.x++;
	// �~�̓}�E�X�ɉ����Ĉړ�
	int mouseX, mouseY;
	GetMousePoint(&mouseX, &mouseY);
	nowMousePos->x = static_cast<float>(mouseX);
	nowMousePos->y = static_cast<float>(mouseY);
	HitKansuu();

	// ����̎l�p�`�Ƃ̑��ΓI�ȃx�N�g�����o���Ă��낢�낳����
	Vector2 rerativeVec = nowCol->GetPos() - boxCol->GetPos();
#if _DEBUG
	printf("�e�X�gm_pos.x=%f, y=%f\n", rerativeVec.x, rerativeVec.y);
	printf("���̌����F%f\n", rerativeVec.Angle());
	DrawLine(static_cast<int>(boxPos.x), static_cast<int>(boxPos.y), static_cast<int>(circlePos.x), static_cast<int>(circlePos.y), 0xffffff);
	printf("45�x���v���ɉ�]\n");
	Vector2 rotatedVec = rerativeVec.RotatedVec(45);
	printf("����x=%f, y=%f\n", rotatedVec.x, rotatedVec.y);
	printf("���̌����F%f\n", rotatedVec.Angle());

	if (input.IsTrigger("ChangeScene_Debug"))
	{
		SceneController::GetInstance().ChangeScene("Game");
		return;
	}
#endif
}

void ColliderTestScene::Draw() const
{
	DrawFormatString(0, 0, color, "FPS=%f", Time::GetInstance().FPS());
	DrawString(0, 15, "ColliderSceneGame", color);
	Vector2 nya = boxCol->GetPos();
	DrawFormatString(0, 30, color, "�R���C�_�[�����Ă�Box1�̈�x%f:y%f", nya.x, nya.y);
	Vector2 nyai = circleCol->GetPos();
	DrawFormatString(0, 45, color, "�R���C�_�[�����Ă�Circle1�̈ʒux%f:y%f", nyai.x, nyai.y);
	DrawCircle(static_cast<int>(circlePos.x), static_cast<int>(circlePos.y), 32, color);
	DrawBox(static_cast<int>(boxPos.x - boxHava.x * 0.5f), static_cast<int>(boxPos.y - boxHava.y * 0.5f), static_cast<int>(boxPos.x + boxHava.x * 0.5f), static_cast<int>(boxPos.y + boxHava.y * 0.5f), color, true);
	DrawCircle(static_cast<int>(circlePos2.x), static_cast<int>(circlePos2.y), 32, color);
	DrawBox(static_cast<int>(boxPos2.x - boxHava.x * 0.5f), static_cast<int>(boxPos2.y - boxHava.y * 0.5f), static_cast<int>(boxPos2.x + boxHava.x * 0.5f), static_cast<int>(boxPos2.y + boxHava.y * 0.5f), color, true);
}
