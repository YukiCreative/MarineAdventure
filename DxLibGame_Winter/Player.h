#pragma once
#include "Vector2.h"
#include <memory>

// 物理クラスのプロトタイプ宣言
class Physics;
class MapSystem;

/// <summary>
/// プレイヤーのクラスです。
/// </summary>
class Player
{
private:
	std::shared_ptr<Physics> m_physics;
	// ざっひょう
	Vector2 m_pos;
public:
	/// <summary>
	/// 初期化
	/// </summary>
	Player();

	/// <summary>
	/// 入力をとって移動したり何したり
	/// </summary>
	void Update(const std::shared_ptr<MapSystem> map);
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 自分のPhysicsのvelocityを返す
	/// いまいちクラス間のデータの受け渡しがわからない
	/// </summary>
	/// <returns></returns>
	Vector2 GetVel();
};

