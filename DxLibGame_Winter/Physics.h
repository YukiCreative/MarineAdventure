#pragma once
#include "Vector2.h"
#include <memory>

class MapChip;

/// <summary>
///  物理挙動をつかさどる
/// </summary>
class Physics
{
private:
	/// <summary>
	/// 加えられた力
	/// </summary>
	Vector2 m_addForce;
	Vector2 m_accel;
	Vector2 m_velocity;
	float m_weight;
	/// <summary>
	/// 物体の体積
	/// これを使って浮力を算出
	/// </summary>
	float m_volume;
	bool m_useConstantForce;

	// 関数ポインタ使うか
	using UpdateFunc_t = Vector2 (Physics::*)();

	UpdateFunc_t m_updateFunc;

public:
	Physics();
	/// <summary>
	/// 必要な値を初期値に入れたコンストラクタ
	/// </summary>
	/// <param name="weight">重さ</param>
	/// <param name="volume">体積</param>
	Physics(float weight, float volume);

	/// <summary>
	/// 物理の更新
	/// この関数で、自分の持っているパラメータと、このフレームに与えられた力から
	/// 自分の1フレームに動く距離を算出する。
	/// </summary>
	Vector2 Update();

	// 水中時と地上時で関数を切り替える
	Vector2 WaterUpdate();
	Vector2 GroundUpdate();

	/// <summary>
	/// 力を加える
	/// </summary>
	/// <param name="_force">力</param>
	void AddForce(Vector2 force);

	/// <summary>
	/// 文字通り速度を返す
	/// </summary>
	/// <returns>現在の速度</returns>
	Vector2 GetVel() const { return m_velocity; }

	/// <summary>
	/// 移動を止める
	/// これ以外で直接velocityをいじるのはできるだけやめよう
	/// </summary>
	void Stop() { m_velocity = Vector2(); }
	/// <summary>
	/// 重力と浮力のいざこざから離れたいときに
	/// </summary>
	void UseConstantForce(bool value) { m_useConstantForce = value; }
};


