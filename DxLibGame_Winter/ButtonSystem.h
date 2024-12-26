#pragma once
#include <list>
#include <memory>

class Button;

// ����
// �{�^�����������񎝂�
// ���͂��{�^���ɍS���A����
// �ǂ̃{�^�����I�΂�Ă��邩�����Ă�����
// �{�^���������ꂽ�Ƃ��A���̃{�^���ɋ����Ă�����@
class ButtonSystem
{
private:
	std::list<std::shared_ptr<Button>> m_buttons;
	// ��̎��́c�k���|�ł����ł����H
	std::shared_ptr<Button> m_nowFocusedButton;
	// �_���ƌ���ꂽ�C�������̂ŁA��t�H�[�J�X����\���{�^�������
	std::shared_ptr<Button> m_dammy;
public:
	ButtonSystem();

	void Update();
};