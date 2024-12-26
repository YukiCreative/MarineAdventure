#pragma once
#include "Vector2.h"
#include "GameObject.h"
#include <string>

// ����
// �J�[�\�����t�H�[�J�X�ł���
// �t�H�[�J�X���ɉ�����
// �����Ɛݒ肳�ꂽ�C�x���g�����s�����
// �C�x���g��Button���p�������N���X�Ŏ���
// �{�^���̃t�H�[�J�X��J�[�\���̏����͕ʂ̃N���X�ł��܂�
class Button : public GameObject
{
private:
	// �摜�Ƃ��e�L�X�g�Ƃ��͔h����Ő錾�������������₷���Ǝv���A�u���Ă��܂���B

	virtual void ForcusedUpdate() = 0;
	virtual void NormalUpdate() = 0;

	using UpdateState_t = void (Button::*)();
	UpdateState_t m_updateState;
public:
	Button(Vector2 initPos);

	void Update() override;
	// Draw�͔h����ł���Ă�

	// �t�H�[�J�X���ꂽ��ButtonSystem���ĂԊ֐�
	void OnForcused();
	// �����ɉ������̌ʏ�����
	virtual void Onpressed() = 0;
};