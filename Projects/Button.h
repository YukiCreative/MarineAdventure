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
// ボタンのフォーカスやカーソルの処理は別のクラスでやる
class Button : public GameObject
{
private:
	// 上下左右の入力がされた時のボタンの遷移先
	// 全てスマートポインタを参照するのでdeleteは要らない
	Button* m_leftButton;
	Button* m_rightButton;
	Button* m_upButton;
	Button* m_downButton;
	// 画像とかテキストとかは派生先で宣言した方が扱いやすいと思って置いていない

	virtual void FocusedUpdate() = 0;
	virtual void NormalUpdate() = 0;

	using UpdateState_t = void (Button::*)();
	UpdateState_t m_updateState;
protected:
	// フォーカスの有無の切り替え
	void InvertState();
public:
	Button(Vector2 initPos);

	// Updateは処理を書いているので上書きしない
	void Update() override final;
	// Drawは派生先でやる

	// フォーカスされたらButtonSystemが呼ぶ関数
	virtual void OnFocused() = 0;
	virtual void OnDisfocused() = 0;
	// ここに押下時の個別処理を
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