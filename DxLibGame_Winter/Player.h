#pragma once
#include "Vector2.h"
#include <memory>

// 物理クラスのプロトタイプ宣言
class Rigid;

/// <summary>
/// プレイヤーのクラスです。
/// </summary>
class Player
{
private:
	std::shared_ptr<Rigid> m_rigid;
public:
	/// <summary>
	/// 初期化
	/// </summary>
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

