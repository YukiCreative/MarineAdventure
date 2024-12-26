#pragma once
#include "Vector2.h"
#include "GameObject.h"
#include <string>

// 役割
// カーソルがフォーカスできる
// フォーカス時に押せる
// 押すと設定されたイベントが実行される
// イベントはButtonを継承したクラスで実装
// ボタンのフォーカスやカーソルの処理は別のクラスでやります
class Button : public GameObject
{
private:
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
	// ここに押下時の個別処理を
	virtual void Onpressed() = 0;
};