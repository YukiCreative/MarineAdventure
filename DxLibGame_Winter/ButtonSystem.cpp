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

	// 今の入力が、前回のフレームと同じ方向ならすぐには動かない

	std::shared_ptr<Button> beforeButton = m_nowFocusedButton;
	// axisを取ってフォーカスの位置をずらす
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

	// ここで何も変わっていなかったら処理終わり
	if (m_nowFocusedButton == beforeButton) return;

	// 新しく選択されたボタンに「お前選ばれてるぞ」と連絡
	m_nowFocusedButton->OnForcused();
	// 元のボタンは通常状態に戻るように連絡
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

	// 選択ボタンの移動処理
	MoveFocus();

	// 登録されているボタンの更新処理をする
	for (auto& button : m_buttons)
	{
		button->Update();
	}
}

void ButtonSystem::AddButton(std::shared_ptr<Button> buttonInstance)
{
	m_buttons.push_back(buttonInstance);
}
