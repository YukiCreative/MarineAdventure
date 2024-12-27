#pragma once
#include "Vector2.h"
#include "GameObject.h"
#include <string>
#include <memory>

// ����
// �J�[�\�����t�H�[�J�X�ł���
// �t�H�[�J�X���ɉ�����
// �����Ɛݒ肳�ꂽ�C�x���g�����s�����
// �C�x���g��Button���p�������N���X�Ŏ���
// �{�^���̃t�H�[�J�X��J�[�\���̏����͕ʂ̃N���X�ł��܂�
class Button : public GameObject
{
private:
	// �㉺���E�̓��͂����ꂽ���̃{�^���̑J�ڐ�
	std::shared_ptr<Button> m_leftButton;
	std::shared_ptr<Button> m_rightButton;
	std::shared_ptr<Button> m_upButton;
	std::shared_ptr<Button> m_downButton;
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
	void OnDisfocused();
	// �����ɉ������̌ʏ�����
	virtual void Onpressed() = 0;

	std::shared_ptr<Button> RightButton() { return m_rightButton; } 
	std::shared_ptr<Button> LeftButton() { return m_leftButton; } 
	std::shared_ptr<Button> UpButton() { return m_upButton; } 
	std::shared_ptr<Button> DownButton() { return m_downButton; } 
};