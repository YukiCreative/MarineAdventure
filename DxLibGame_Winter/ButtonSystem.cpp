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

	// 今の入力が、前回のフレームと同じ方向ならすぐには動かない
	if (inputAxis.RerativeAngle(m_inputDirBeforeFrame) < kAxisDirThreshold)
	{
		// この場合、タイマーが一定時間経過しているか確かめる
		if (m_cursorMoveTimer > 0) return;
	}

	Vector2Int inputDir(0,0);
	std::weak_ptr<Button> beforeButton = m_nowFocusedButton;
	// axisを取ってフォーカスの位置をずらす
	if (inputAxis.x > kButtonPosMoveThreshold)
	{
		m_nowFocusedButton = GetWeakPtr(m_nowFocusedButton.lock()->RightButton());
		++inputDir.x;
	}
	else if (inputAxis.x < -kButtonPosMoveThreshold)
	{
		m_nowFocusedButton = GetWeakPtr(m_nowFocusedButton.lock()->LeftButton());
		--inputDir.x;
	}
	if (inputAxis.y > kButtonPosMoveThreshold)
	{
		m_nowFocusedButton = GetWeakPtr(m_nowFocusedButton.lock()->DownButton());
		++inputDir.y;
	}
	else if (inputAxis.y < -kButtonPosMoveThreshold)
	{
		m_nowFocusedButton = GetWeakPtr(m_nowFocusedButton.lock()->UpButton());
		--inputDir.y;
	}

	// 今の入力を記憶
	m_inputDirBeforeFrame = inputDir;

	// ここで何も変わっていなかったら処理終わり
	if (m_nowFocusedButton.lock() == beforeButton.lock()) return;

	// 新しく選択されたボタンに「お前選ばれてるぞ」と連絡
	m_nowFocusedButton.lock()->OnFocused();
	// 元のボタンは通常状態に戻るように連絡
	beforeButton.lock()->OnDisfocused();
	printf("before参照数：%d", beforeButton.use_count());
	// タイマーを設定
	m_cursorMoveTimer = kCursorMoveInterval;
}

std::weak_ptr<Button> ButtonSystem::GetWeakPtr(Button* rawPtr)
{
	for (const auto& button : m_buttons)
	{
		if (button.get() == rawPtr)
		{
			return button;
		}
	}

	assert(false && "ボタン一覧にそんなボタンがなかったから追加していないのでは？");
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

	// 選択ボタンの移動処理
	MoveFocus();

	// 登録されているボタンの更新処理をする
	for (auto& button : m_buttons)
	{
		button->Update();
	}

	// ボタン押したときの処理
	if (Input::GetInstance().IsTrigger("Submit"))
	{
		m_nowFocusedButton.lock()->OnPressed();
		// すぐにシーン遷移するかもしれないのでreturnしとく
		return;
	}
}

void ButtonSystem::Draw() const
{
	// ボタンの描画関数を実行
	for (const auto& button : m_buttons)
	{
		button->Draw();
		printf("参照数:%d", button.use_count());
	}
}

void ButtonSystem::AddButton(std::shared_ptr<Button> buttonInstance)
{
	m_buttons.push_back(buttonInstance);
}

void ButtonSystem::SetButtonFocus(std::shared_ptr<Button> setButton)
{
	assert(std::find(m_buttons.begin(), m_buttons.end(), setButton) != m_buttons.end() && "登録されていないボタンです");
	m_nowFocusedButton.lock()->OnDisfocused();
	m_nowFocusedButton = setButton;
	m_nowFocusedButton.lock()->OnFocused();
}

void ButtonSystem::ExitFocus()
{
	m_nowFocusedButton = std::static_pointer_cast<Button>(m_noFocus);
}
