#pragma once
#include <list>
#include <memory>
#include "Vector2.h"

class Button;
class ButtonNoFocus;

enum class InputDir
{
	kNone,
	kRight,
	kLeft,
	kUp,
	kDown
};

// ����
// �{�^�����������񎝂�
// ���͂��{�^���ɍS���A����
// �ǂ̃{�^�����I�΂�Ă��邩�����Ă�����
// �{�^���������ꂽ�Ƃ��A���̃{�^���ɋ����Ă�����@
class ButtonSystem
{
private:
	using ButtonList_t = std::list<std::shared_ptr<Button>>;
	ButtonList_t m_buttons;
	// ��̎��́c�k���|�ł����ł����H
	std::shared_ptr<Button> m_nowFocusedButton;
	// �_���ƌ���ꂽ�C�������̂ŁA��t�H�[�J�X����\���{�^�������
	std::shared_ptr<ButtonNoFocus> m_noFocus;
	// ���������ɓ��͂��������瓮���A���̃^�C�}�[
	int m_cursorMoveTimer;
	InputDir m_inputDirBeforeFrame;

	void MoveFocus();
public:
	ButtonSystem();

	// ���͂���ǂ̃{�^����I�����Ă��邩��ς����肷��
	void Update();

	// �{�^����ǉ�
	// �V�[�������p����z��
	void AddButton(std::shared_ptr<Button> buttonInstance);

	void SetButtonFocus(std::shared_ptr<Button> setButton) { m_nowFocusedButton = setButton; }
	void ExitFocus() { m_nowFocusedButton = std::static_pointer_cast<Button>(m_noFocus); }
};