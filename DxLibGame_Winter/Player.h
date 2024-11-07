#pragma once
#include "Vector2.h"

/// <summary>
/// プレイヤーのクラスです。
/// </summary>
class Player
{
private:
	Vector2 m_pos;
public:
	Player();

	/// <summary>
	/// 入力を取って移動したり何たり
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
};

