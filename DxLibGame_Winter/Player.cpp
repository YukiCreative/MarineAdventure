#include "Player.h"
#include <DxLib.h>
#include "Input.h"
#include "Rigid.h"

namespace
{
	// ���e�X�g
	int kRaduis = 10;

	constexpr float kInitPosX = 100;
	constexpr float kInitPosY = 100;
}

Player::Player() :
	m_rigid(std::make_shared<Rigid>(Vector2(kInitPosX, kInitPosY), 1.0f))
{
}

void Player::Update()
{
	// ���͂��Ƃ��āA�����B
	Input& input = Input::GetInstance();

	if (input.IsPressed(PAD_INPUT_1))
	{
		// �͂�������

	}

	// ������Update�͓��͂Ȃǂŗ͂��Z�o���I�������Ɏ��s���邱�ƁB
	m_rigid->Update();
}

void Player::Draw()
{
	// Rigid�C���X�^���X������W���R�s�[���Ă���
	Vector2 copyPos = m_rigid->GetPos();
	DrawCircle(copyPos.x, copyPos.y, 10, 0xff0000);
#if _DEBUG
	DrawFormatString(0, 20, 0xffffff, "PlayerPos:x = %f, y = %f", copyPos.x, copyPos.y);
#endif
}
