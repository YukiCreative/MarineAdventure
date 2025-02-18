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
// �{�^���̃t�H�[�J�X��J�[�\���̏����͕ʂ̃N���X�ł��
class Button : public GameObject
{
private:
	// �㉺���E�̓��͂����ꂽ���̃{�^���̑J�ڐ�
	// �S�ăX�}�[�g�|�C���^���Q�Ƃ���̂�delete�͗v��Ȃ�
	Button* m_leftButton;
	Button* m_rightButton;
	Button* m_upButton;
	Button* m_downButton;
	// �摜�Ƃ��e�L�X�g�Ƃ��͔h����Ő錾�������������₷���Ǝv���Ēu���Ă��Ȃ�

	virtual void FocusedUpdate() = 0;
	virtual void NormalUpdate() = 0;

	using UpdateState_t = void (Button::*)();
	UpdateState_t m_updateState;
protected:
	// �t�H�[�J�X�̗L���̐؂�ւ�
	void InvertState();
public:
	Button(Vector2 initPos);

	// Update�͏����������Ă���̂ŏ㏑�����Ȃ�
	void Update() override final;
	// Draw�͔h����ł��

	// �t�H�[�J�X���ꂽ��ButtonSystem���ĂԊ֐�
	virtual void OnFocused() = 0;
	virtual void OnDisfocused() = 0;
	// �����ɉ������̌ʏ�����
	virtual void OnPressed() = 0;

	void SetRightButton(std::shared_ptr<Button> right) { m_rightButton = right.get(); }
	void SetLeftButton (std::shared_ptr<Button> left ) { m_leftButton  =  left.get(); }
	void SetUpButton   (std::shared_ptr<Button> up   ) { m_upButton    =    up.get(); }
	void SetDownButton (std::shared_ptr<Button> down ) { m_downButton  =  down.get(); }

	Button* RightButton() const { return m_rightButton; }
	Button* LeftButton()  const { return m_leftButton;  }
	Button* UpButton()    const { return m_upButton;    }
	Button* DownButton()  const { return m_downButton;  }
};