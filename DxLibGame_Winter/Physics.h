#pragma once
#include "Vector2.h"

/// <summary>
///  物理挙動をつかさどりたい
///  速度を持っていて、座標も持とうかな
/// </summary>
class Physics
{
private:
	/// <summary>
	/// 加えられた力
	/// </summary>
	Vector2 m_addForce;
	Vector2 m_accel;
	Vector2 m_position;
	Vector2 m_velocity;
	float m_weight;
	/// <summary>
	/// 物体の体積
	/// これを使って浮力を算出
	/// </summary>
	float m_volume;

	// 関数ポインタ使うか
	using UpdateFunc_t = void (Physics::*)();

	UpdateFunc_t m_updateFunc;

public:
	Physics();
	/// <summary>
	/// 必要な値を初期値に入れたコンストラクタ
	/// </summary>
	/// <param name="weight"></param>
	Physics(Vector2 initPos, float weight, float volume);

	/// <summary>
	/// 物理の更新
	/// この関数で、速度に応じて毎フレーム座標を移動させたり、
	/// その速度を抵抗によって減らしたりする
	/// </summary>
	void Update();

	// 水中時と地上時で関数を切り替える
	void WaterUpdate();
	void GroundUpdate();

	/// <summary>
	/// 力を加える
	/// </summary>
	/// <param name="_force">力</param>
	void AddForce(Vector2 force);

	/// <summary>
	/// 自分の座標を返す
	/// </summary>
	/// <returns>Vector2型の座標</returns>
	Vector2 GetPos() { return m_position; }
};


