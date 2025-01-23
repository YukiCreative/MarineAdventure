#pragma once
#include "Vector2.h"
#include "game.h"
#include <memory>
#include "GameObject.h"

class MapSystem;

/// <summary>
/// オブジェクトのワールド座標を描画のスクリーン座標に変換
/// </summary>
class Camera
{
private:
	Vector2 m_pos;
	// マップのチップ数を知っておきたい
	Vector2Int m_mapSize;
	Vector2 m_drawOffset;
	// 今回のフレームの移動量を記憶しておく
	Vector2 m_velocity;
	// Moveの移動量記憶用
	Vector2 m_moveAmount;
	/// <summary>
	/// 参照するゲームオブジェクト
	/// </summary>
	std::weak_ptr<GameObject> m_refObj;
public:
	Camera() = default;
	// カメラの初期位置だけ入れられるようにする
	Camera(Vector2 initPos) : m_pos(initPos) {}

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
	void Move(const Vector2& moveValue) { m_moveAmount += moveValue; }
	void Teleport(const Vector2& pos) { m_pos = pos; }

	void SetMapSize(Vector2Int mapSize) { m_mapSize = mapSize; };

	Vector2 GetPos() const { return m_pos; };
	// これを座標から引けばスクリーン座標になります
	// でもいつもはCaptureを使ってほしい
	Vector2 DrawOffset() const { return m_drawOffset; }

	/// <summary>
	/// 引数に入れられたゲームオブジェクトに追従する
	/// </summary>
	void SetFollowObject(std::weak_ptr<GameObject> obj) { m_refObj = obj; }
	void ResetFollowObject() { m_refObj.reset(); };
	Vector2 GetVel() { return m_velocity; }
};

