#pragma once
#include "Vector2.h"
#include "game.h"
#include <memory>
#include "GameObject.h"

/// <summary>
/// オブジェクトのワールド座標を描画のスクリーン座標に変換
/// </summary>
class Camera : public GameObject
{
private:
	/// <summary>
	/// Updateで一括で移動するために一時的に記憶しておく
	/// </summary>
	Vector2 m_velocity;
	/// <summary>
	/// 参照するゲームオブジェクト
	/// </summary>
	std::shared_ptr<GameObject> m_refObj;
public:
	/// <summary>
	/// カメラの更新
	/// </summary>
	void Update() 
	{
		m_pos += m_velocity;
		// 移動量リセ
		m_velocity = Vector2();
	}
	/// <summary>
	/// 引数に入れられたワールド座標を、現在のカメラのワールド座標によってスクリーン座標に変換
	/// </summary>
	/// <param name="pos">ワールド座標</param>
	/// <returns>スクリーン座標</returns>
	Vector2 Capture(const Vector2& objPos) const
	{
		Vector2 screenPos = objPos - m_pos;
		// スクリーンの中央になるように補正
		screenPos.x += Game::kScreenWidth * 0.5f;
		screenPos.y += Game::kScreenHeight * 0.5f;
		return screenPos;
	}
	/// <summary>
	/// カメラの移動
	/// </summary>
	void Move(Vector2 moveValue) { m_pos += moveValue; }

	Vector2 GetPos() const { return m_pos; };

	/// <summary>
	/// 引数に入れられたゲームオブジェクトに追従する
	/// 次に別のオブジェクトか、nullptrがSetされるまで継続
	/// </summary>
	void SetFollowObject(std::shared_ptr<GameObject> obj)
	{
		// nullptrの可能性あり
		m_refObj = obj;
	}
};

