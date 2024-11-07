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

	void operator/=(Vector2 right)
	{
		x /= right.x;
		y /= right.y;
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
};
