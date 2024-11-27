#pragma once
#include <cmath>
#include <DxLib.h>
// このスクリプトには特に、何もincludeしないこと！

/// <summary>
/// ヘッダオンリーの構造体
/// </summary>
struct Vector2
{
public:
	float x, y;

	Vector2() : x(0), y(0)
	{
	}

	Vector2(float _x, float _y) : x(_x), y(_y)
	{
	}

	// 変換コンストラクタ
	// これがあるおかげでfloatとの演算子オーバーロードをしなくて済む
	// (Vector2を作るからちょっと遅いらしいけど)
	Vector2(float value) : x(value), y(value)
	{
	}

	// このVecor2が、VECTORをいれる場所に入ったら、暗黙的に変換される
	// DxLibインクルードしてるけどしょうがない
	operator VECTOR()
	{
		return VGet(x, y, 0.0f);
	}

	/// <summary>
	/// 左辺に、右辺を足し算したものを代入
	/// </summary>
	/// <param name="right">右辺</param>
	void operator+=(const Vector2& right)
	{
		x += right.x;
		y += right.y;
	}

	void operator-=(const Vector2& right)
	{
		x -= right.x;
		y -= right.y;
	}

	Vector2 operator*(const float& right) const
	{
		Vector2 result;
		result.x = x * x;
		result.y = y * y;
		return result;
	}

	void operator*=(const float& right)
	{
		x *= right;
		y *= right;
	}

	void operator/=(const float& right)
	{
		x /= right;
		y /= right;
	}

	Vector2 operator/(const float& right) const
	{
		Vector2 result;
		result.x = x / right;
		result.y = y / right;
		return result;
	}

	Vector2 operator+(const Vector2& other) const
	{
		Vector2 result;
		result.x = x + other.x;
		result.y = y + other.y;
		return result;
	}

	Vector2 operator-()
	{
		return Vector2(-x, -y);
	}

	// 増え続けるオーバーロードォ…
	Vector2 operator-(const Vector2& other) const
	{
		Vector2 result;
		result.x = x - other.x;
		result.y = y - other.y;
		return result;
	}

	/// <summary>
	/// 大きさの二乗を返す
	/// </summary>
	/// <returns>ベクトルの大きさの二乗</returns>
	float SqrMagnitude()
	{
		return x * x + y * y;
	}

	/// <summary>
	///  大きさ返す
	/// </summary>
	/// <returns>大きさ</returns>
	float Magnitude()
	{
		return std::sqrtf(x * x + y * y);
	}

	/// <summary>
	/// 自分を単位ベクトルにする
	/// </summary>
	void Normalize()
	{
		float mag = Magnitude();
		// 大きさが0ならreturn
		if (!mag) return;
		// 自分の成分を自分の大きさで割る
		x = x / mag;
		y = y / mag;
	}

	/// <summary>
	/// 単位ベクトルにしたコピーを返す
	/// </summary>
	/// <returns>単位ベクトル(コピー)</returns>
	Vector2 GetNormalize()
	{
		Vector2 result;
		float mag = Magnitude();
		if (!mag) return *this;
		result.x = x / mag;
		result.y = y / mag;
		return result;
	}

	/// <summary>
	/// startからendまでrate分進んだベクトルを返す
	/// </summary>
	/// <param name="start">初期位置</param>
	/// <param name="end">ゴール</param>
	/// <param name="rate">割合0~1</param>
	/// <returns>startからendにrate分進んだベクトル</returns>
	static Vector2 Lerp(const Vector2& start, const Vector2& end, const float& rate)
	{
		// std::clampを使おうとしたがインクルードが必要なので止めた
		float clampRate;
		if (rate < 0)
		{
			clampRate = 0;
		}
		else if (rate > 1)
		{
			clampRate = 1;
		}
		else
		{
			clampRate = rate;
		}
		Vector2 lerp = start;
		lerp += (end - start) * clampRate;
		return lerp;
	}

	// (0, 0)
	static Vector2 Zero()
	{
		return Vector2();
	}
	// (0, -1)
	static Vector2 Up()
	{
		return Vector2(0, -1);
	}
	// (0, 1)
	static Vector2 Down()
	{
		return Vector2(0, 1);
	}
	// (1, 0)
	static Vector2 Right()
	{
		return Vector2(1, 0);
	}
	// (-1, 0)
	static Vector2 Left()
	{
		return Vector2(-1, 0);
	}
};