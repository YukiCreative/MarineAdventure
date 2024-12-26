#pragma once
#include <list>
#include <memory>

class Button;

// 役割
// ボタンをたくさん持つ
// 入力をボタンに拘束、解除
// どのボタンが選ばれているか教えてあげる
// ボタンが押されたとき、そのボタンに教えてあげる　
class ButtonSystem
{
private:
	std::list<std::shared_ptr<Button>> m_buttons;
	// 空の時は…ヌルポでいいですか？
	std::shared_ptr<Button> m_nowFocusedButton;
	// ダメと言われた気がしたので、非フォーカス時を表すボタンを作る
	std::shared_ptr<Button> m_dammy;
public:
	ButtonSystem();

	void Update();
};