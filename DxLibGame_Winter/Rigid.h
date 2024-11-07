#pragma once
#include "Vector2.h"

/// <summary>
///  物理挙動をつかさどりたい
///  速度を持っていて、座標も持とうかな
/// </summary>
class Rigid
{
private:
	Vector2 force;
	Vector2 accel;
	Vector2 position;
	float weight;
	/// <summary>
	/// 水中移動時の抵抗
	/// </summary>
	float waterResistance;
	float airResistance;
public:
	Rigid();

	/// <summary>
	/// 物理の更新
	/// この関数で、速度に応じて毎フレーム座標を移動させたり、
	/// その速度を抵抗によって減らしたりする
	/// </summary>
	void Update();
};

