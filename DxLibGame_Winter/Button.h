#pragma once
#include "Vector2.h"
#include "GameObject.h"
#include <string>
#include <memory>

// 役割
// カーソルがフォーカスできる
// フォーカス時に押せる
// 押すと設定されたイベントが実行される
// イベントはButtonを継承したクラスで実装
// ボタンのフォーカスやカーソルの処理は別のクラスでやります
class Button : public GameObject
{
private:
	// 上下左右の入力がされた時のボタンの遷移先
	// 全てスマートポインタを参照するのでdeleteは要らない
	Button* m_leftButton;
	Button* m_rightButton;
	Button* m_upButton;
	Button* m_downButton;
	// 画像とかテキストとかは派生先で宣言した方が扱いやすいと思い、置いていません。

	virtual void ForcusedUpdate() = 0;
	virtual void NormalUpdate() = 0;

	using UpdateState_t = void (Button::*)();
	UpdateState_t m_updateState;
public:
	Button(Vector2 initPos);

	void Update() override;
	// Drawは派生先でやってね

	// フォーカスされたらButtonSystemが呼ぶ関数
	void OnForcused();
	void OnDisfocused();
	// ここに押下時の個別処理を
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