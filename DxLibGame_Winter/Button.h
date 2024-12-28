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
	// �S�ăX�}�[�g�|�C���^���Q�Ƃ���̂�delete�͗v��Ȃ�
	Button* m_leftButton;
	Button* m_rightButton;
	Button* m_upButton;
	Button* m_downButton;
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

	void SetRightButton(std::shared_ptr<Button> right) { m_rightButton = right.get(); }
	void SetLeftButton(std::shared_ptr<Button> left) { m_leftButton = left.get(); }
	void SetUpButton(std::shared_ptr<Button> up) { m_upButton = up.get(); }
	void SetDownButton(std::shared_ptr<Button> down) { m_downButton = down.get(); }

	std::shared_ptr<Button> RightButton() const { return std::shared_ptr<Button>(m_rightButton); }
	std::shared_ptr<Button> LeftButton() const { return std::shared_ptr<Button>(m_leftButton); }
	std::shared_ptr<Button> UpButton() const { return std::shared_ptr<Button>(m_upButton); }
	std::shared_ptr<Button> DownButton() const { return std::shared_ptr<Button>(m_downButton); }
};