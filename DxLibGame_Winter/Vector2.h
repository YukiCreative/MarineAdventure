#pragma once
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

	/// <summary>
	/// 大きさの二乗を返す
	/// </summary>
	/// <returns>ベクトルの大きさの二乗</returns>
	float SqrMagnitude()
	{
		return x * x + y * y;
	}

	/// <summary>
	/// 自分を単位ベクトルにする
	/// </summary>
	void Normalize()
	{
		float mag = SqrMagnitude();
		// 大きさが0ならreturn
		if (!mag) return;
		// 自分の成分を自分の大きさで割る(二乗)
		x = (x * x) / mag;
		y = (y * y) / mag;
	}

	/// <summary>
	/// 単位ベクトルにしたコピーを返す
	/// </summary>
	/// <returns>単位ベクトル(コピー)</returns>
	Vector2 GetNormalize()
	{
		Vector2 result;
		float mag = SqrMagnitude();
		if (!mag) return result;
		result.x = (x * x) / mag;
		result.y = (y * y) / mag;
		return result;
	}
};
