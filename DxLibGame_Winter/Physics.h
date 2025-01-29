#pragma once
#include "Vector2.h"
#include <memory>
#include "MapConstants.h"
#include <array>
#include <list>

class kMapChip;

/// <summary>
/// 物理挙動をつかさどる
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
	// 接地しているか
	// 本当は空中と地上で状態関数を分けるべきなのですが、変更箇所が膨大なのでGroundUpdate内で分岐します
	// どうしてこうなった
	bool m_isGrounded;

	// 関数ポインタ使うか
	using UpdateState_t = Vector2(Physics::*)();
	UpdateState_t m_updateState;
	std::array<UpdateState_t, static_cast<int>(MapConstants::kEnvironment::kEnvNum)> m_stateArray =
	{
		&Physics::WaterUpdate,
		&Physics::GroundUpdate,
	};

	// 水中時と地上時で関数を切り替える
	Vector2 WaterUpdate();
	Vector2 GroundUpdate();
public:
	Physics();
	// 必要な値を初期値に入れたコンストラクタ
	Physics(float weight, float volume);

	// この関数で、自分の持っているパラメータと、このフレームに与えられた力から
	// 自分の1フレームに動く距離を算出する。
	Vector2 Update();

	// 力を加える
	void AddForce(Vector2 force);

	/// 文字通り速度を返す
	Vector2 GetVel() const { return m_velocity; }

	/// <summary>
	/// 移動を止める
	/// これ以外で直接velocityをいじるのはできるだけやめよう
	/// </summary>
	void Stop() { m_velocity = Vector2::Zero(); }
	void StopY() { m_velocity.y = 0; }
	/// <summary>
	/// 重力と浮力のいざこざから離れたいときに
	/// </summary>
	void UseConstantForce(bool value) { m_useConstantForce = value; }

	// 与えられた列挙に対応した状態かどうかを返す
	bool CheckState(const MapConstants::kEnvironment&) const;
	void ChangeState(const MapConstants::kEnvironment&);
	void InvertState();
	MapConstants::kEnvironment GetNowEnvironment() const;
	void IsGrounded(const bool& value) { m_isGrounded = value; }
};