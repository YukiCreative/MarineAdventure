#include "ButtonSystem.h"
#include "Input.h"
#include "Button.h"
#include "ButtonNoFocus.h"

namespace
{
	constexpr int kButtonPosMoveThreshold = 300;
	constexpr int kCursorMoveInterval = 20;
}

void ButtonSystem::MoveFocus()
{
	Vector2 inputAxis = Input::GetInstance().GetInputAxis();

	// ���̓��͂��A�O��̃t���[���Ɠ��������Ȃ炷���ɂ͓����Ȃ�

	std::shared_ptr<Button> beforeButton = m_nowFocusedButton;
	// axis������ăt�H�[�J�X�̈ʒu�����炷
	if (inputAxis.x > kButtonPosMoveThreshold)
	{
		m_nowFocusedButton = m_nowFocusedButton->RightButton();
	}
	else if (inputAxis.x < -kButtonPosMoveThreshold)
	{
		m_nowFocusedButton = m_nowFocusedButton->LeftButton();
	}
	if (inputAxis.y > kButtonPosMoveThreshold)
	{
		m_nowFocusedButton = m_nowFocusedButton->DownButton();
	}
	else if (inputAxis.y < -kButtonPosMoveThreshold)
	{
		m_nowFocusedButton = m_nowFocusedButton->UpButton();
	}

	// �����ŉ����ς���Ă��Ȃ������珈���I���
	if (m_nowFocusedButton == beforeButton) return;

	// �V�����I�����ꂽ�{�^���Ɂu���O�I�΂�Ă邼�v�ƘA��
	m_nowFocusedButton->OnForcused();
	// ���̃{�^���͒ʏ��Ԃɖ߂�悤�ɘA��
	beforeButton->OnDisfocused();
}

ButtonSystem::ButtonSystem() :
	m_cursorMoveTimer(0),
	m_inputDirBeforeFrame(InputDir::kNone)
{
	m_noFocus = std::make_shared<ButtonNoFocus>();
}

void ButtonSystem::Update()
{
	--m_cursorMoveTimer;

	// �I���{�^���̈ړ�����
	MoveFocus();

	// �o�^����Ă���{�^���̍X�V����������
	for (auto& button : m_buttons)
	{
		button->Update();
	}
}

void ButtonSystem::AddButton(std::shared_ptr<Button> buttonInstance)
{
	m_buttons.push_back(buttonInstance);
}
