#include "ButtonSystem.h"
#include "Input.h"
#include "Button.h"
#include "ButtonNoFocus.h"
#include <cassert>

namespace
{
	constexpr int kButtonPosMoveThreshold = 300;
	constexpr int kCursorMoveInterval = 20;
	constexpr int kAxisDirThreshold = 45;
}

void ButtonSystem::MoveFocus()
{
	Vector2 inputAxis = Input::GetInstance().GetInputAxis();

	// ���̓��͂��A�O��̃t���[���Ɠ��������Ȃ炷���ɂ͓����Ȃ�
	if (inputAxis.RerativeAngle(m_inputDirBeforeFrame) < kAxisDirThreshold)
	{
		// ���̏ꍇ�A�^�C�}�[����莞�Ԍo�߂��Ă��邩�m���߂�
		if (m_cursorMoveTimer > 0) return;
	}

	Vector2Int inputDir(0,0);
	std::shared_ptr<Button> beforeButton = m_nowFocusedButton;
	// axis������ăt�H�[�J�X�̈ʒu�����炷
	if (inputAxis.x > kButtonPosMoveThreshold)
	{
		m_nowFocusedButton = m_nowFocusedButton->RightButton();
		++inputDir.x;
	}
	else if (inputAxis.x < -kButtonPosMoveThreshold)
	{
		m_nowFocusedButton = m_nowFocusedButton->LeftButton();
		--inputDir.x;
	}
	if (inputAxis.y > kButtonPosMoveThreshold)
	{
		m_nowFocusedButton = m_nowFocusedButton->DownButton();
		++inputDir.y;
	}
	else if (inputAxis.y < -kButtonPosMoveThreshold)
	{
		m_nowFocusedButton = m_nowFocusedButton->UpButton();
		--inputDir.y;
	}

	// ���̓��͂��L��
	m_inputDirBeforeFrame = inputDir;

	// �����ŉ����ς���Ă��Ȃ������珈���I���
	if (m_nowFocusedButton == beforeButton) return;

	// �V�����I�����ꂽ�{�^���Ɂu���O�I�΂�Ă邼�v�ƘA��
	m_nowFocusedButton->OnForcused();
	// ���̃{�^���͒ʏ��Ԃɖ߂�悤�ɘA��
	beforeButton->OnDisfocused();
	// �^�C�}�[��ݒ�
	m_cursorMoveTimer = kCursorMoveInterval;
}

ButtonSystem::ButtonSystem() :
	m_cursorMoveTimer(0),
	m_inputDirBeforeFrame(0,0)
{
	m_noFocus = std::make_shared<ButtonNoFocus>();
	m_nowFocusedButton = m_noFocus;
}

ButtonSystem::~ButtonSystem()
{
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

	// �{�^���������Ƃ��̏���
	if (Input::GetInstance().IsTrigger("Submit"))
	{
		m_nowFocusedButton->OnPressed();
		// �����ɃV�[���J�ڂ��邩������Ȃ��̂�return���Ƃ�
		return;
	}
}

void ButtonSystem::Draw() const
{
	// �{�^���̕`��֐������s
	for (const auto& button : m_buttons)
	{
		button->Draw();
	}
}

void ButtonSystem::AddButton(std::shared_ptr<Button> buttonInstance)
{
	m_buttons.push_back(buttonInstance);
}

void ButtonSystem::SetButtonFocus(std::shared_ptr<Button> setButton)
{
	assert(std::find(m_buttons.begin(), m_buttons.end(), setButton) != m_buttons.end() && "�o�^����Ă��Ȃ��{�^���ł�");
	m_nowFocusedButton->OnDisfocused();
	m_nowFocusedButton = setButton;
	m_nowFocusedButton->OnForcused();
}

void ButtonSystem::ExitFocus()
{
	m_nowFocusedButton = std::static_pointer_cast<Button>(m_noFocus);
}
