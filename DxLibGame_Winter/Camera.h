#pragma once
#include "Vector2.h"
#include "game.h"
#include <memory>
#include "GameObject.h"

/// <summary>
/// オブジェクトのワールド座標を描画のスクリーン座標に変換
/// </summary>
class Camera
{
private:
	Vector2 m_pos;
	Vector2 m_drawOffset;
	/// <summary>
	/// Updateで一括で移動するために一時的に記憶しておく
	/// </summary>
	Vector2 m_velocity;
	/// <summary>
	/// 参照するゲームオブジェクト
	/// </summary>
	std::weak_ptr<GameObject> m_refObj;
public:
	/// <summary>
	/// カメラの更新
	/// </summary>
	void Update();
	/// <summary>
	/// 引数に入れられたワールド座標を、現在のカメラのワールド座標によってスクリーン座標に変換
	/// </summary>
	/// <param name="pos">ワールド座標</param>
	/// <returns>スクリーン座標</returns>
	Vector2 Capture(const Vector2& objPos) const;
	/// <summary>
	/// カメラの移動
	/// </summary>
	void Move(Vector2 moveValue) { m_pos += moveValue; }

	Vector2 GetPos() const { return m_pos; };

	/// <summary>
	/// 引数に入れられたゲームオブジェクトに追従する
	/// </summary>
	void SetFollowObject(std::weak_ptr<GameObject> obj);
	void ResetFollowObject() { m_refObj.reset(); };
};

