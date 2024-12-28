#pragma once
#include <list>
#include <memory>
#include "Vector2.h"

class Button;
class ButtonNoFocus;

// 役割
// ボタンをたくさん持つ
// 入力をボタンに拘束、解除
// どのボタンが選ばれているか教えてあげる
// ボタンが押されたとき、そのボタンに教えてあげる　
class ButtonSystem
{
private:
	using ButtonList_t = std::list<std::shared_ptr<Button>>;
	ButtonList_t m_buttons;
	// 空の時は…ヌルポでいいですか？
	std::shared_ptr<Button> m_nowFocusedButton;
	// ダメと言われた気がしたので、非フォーカス時を表すボタンを作る
	std::shared_ptr<ButtonNoFocus> m_noFocus;
	// 同じ方向に入力し続けたら動くアレのタイマー
	int m_cursorMoveTimer;
	Vector2Int m_inputDirBeforeFrame;

	void MoveFocus();
public:
	ButtonSystem();
	~ButtonSystem();

	// 入力からどのボタンを選択しているかを変えたりする
	void Update();
	
	void Draw() const;

	// ボタンを追加
	// シーンが利用する想定
	void AddButton(std::shared_ptr<Button> buttonInstance);

	void SetButtonFocus(std::shared_ptr<Button> setButton);
	void ExitFocus();
};