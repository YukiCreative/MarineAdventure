#include "ScreenEffectController.h"
#include <DxLib.h>
#include "game.h"

// �t�F�[�h�C���A�E�g�̏���
ScreenEffectController::ScreenFade::ScreenFade(int frame, float fadePercent, unsigned int color) :
	m_color(color),
	m_lifeFrame(frame),
	m_percent(fadePercent)
{
	// �^����ꂽ���ƍ��̃t�F�[�h�p�l���̓����x����A
	// �ʒu�t���[���ɂǂꂾ�������x�𑀍삷��΂����̂�������o��
}

void ScreenEffectController::ScreenFade::Update()
{

}

// ==================================

void ScreenEffectController::Update()
{
	if (m_screenEffects.empty()) return;

	bool isFinished = true;
	for (auto& effect : m_screenEffects.front())
	{
		isFinished &= effect->IsFinished();
	}
	// ���̃L���[�̂��ׂẲ摜���ʂ��I�������
	if (isFinished)
	{
		// ���o��
		m_screenEffects.pop_front();
	}
	// �C����蒼����Update
	for (auto& effect : m_screenEffects.front())
	{
		effect->Update();
	}
}

void ScreenEffectController::Draw() const
{
	// ������FadePanel��Draw
	m_fadePanel->Draw();
}

// ============================

void ScreenEffectController::FadePanel::Draw() const
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_alpha);
	// ��ʂ����ς��ɕ`��
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, m_color, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
