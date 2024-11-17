#pragma once
#include <cmath>
// このスクリプトには特に、何もincludeしないこと！

/// <summary>
/// ヘッダオンリーの構造体
/// </summary>
struct Vector2
{
public:
	float x, y;

	Vector2()
	{
		x = 0;
		y = 0;
	}

	Vector2(float _x, float _y)
	{
		x = _x;
		y = _y;
	}

	
	/// <summary>
	/// 左辺に、右辺を足し算したものを代入
	/// </summary>
	/// <param name="right">右辺</param>
	void operator+=(Vector2 right)
	{
		x += right.x;
		y += right.y;
	}

	void operator-=(Vector2 right)
	{
		x -= right.x;
		y -= right.y;
	}

	void operator*=(Vector2 right)
	{
		x *= right.x;
		y *= right.y;
	}

	void operator*=(float right)
	{
		x *= right;
		y *= right;
	}

	void operator/=(Vector2 right)
	{
		x /= right.x;
		y /= right.y;
	}

	void operator/=(float right)
	{
		x /= right;
		y /= right;
	}

	Vector2 operator/(float other)
	{
		// 一回でも割り算を減らす
		// 意味があるのかは知らん！
		float factor = 1 / other;

		Vector2 result;
		result.x = x * factor;
		result.y = y * factor;
		return result;
	}

	Vector2 operator*(float other)
	{
		Vector2 result;
		result.x = x * other;
		result.y = y * other;
		return result;
	}

	Vector2 operator+(float other)
	{
		Vector2 result;
		result.x = x + other;
		result.y = y + other;
		return result;
	}

	Vector2 operator+(Vector2 other)
	{
		Vector2 result;
		result.x = x + other.x;
		result.y = y + other.y;
		return result;
	}

	Vector2 operator-(float other)
	{
		Vector2 result;
		result.x = x - other;
		result.y = y - other;
		return result;
	}

	Vector2 operator-(Vector2 other)
	{
		Vector2 result;
		result.x = x - other.x;
		result.y = y - other.y;
		return result;
	}

	// 増え続けるオーバーロードォ…
	Vector2 operator-(Vector2 other) const
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
		// 自分の成分を自分の大きさで割る(二乗)
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
};
