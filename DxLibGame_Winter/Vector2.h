#pragma once
#include <cmath>
#include <limits>
#include <DxLib.h>
#include "Calculation.h"
// このスクリプトには特に、何もincludeしないこと！

/// <summary>
/// ヘッダオンリーの構造体
/// </summary>
struct Vector2
{
protected:
	// NaV用
	Vector2(bool valid) : x(0), y(0), isValid(valid) {}

public:
	float x, y;
	bool isValid;

	Vector2() : x(0), y(0), isValid(true)
	{
	}

	Vector2(const float& _x, const float& _y) : x(_x), y(_y), isValid(true)
	{
	}

	Vector2(const int& _x, const int& _y) : x(static_cast<float>(_x)), y(static_cast<float>(_y)), isValid(true)
	{
	}

	// floatからの変換コンストラクタ
	// floatの演算子オーバーロードを省略できる
	Vector2(const float& value) : x(value), y(value), isValid(true)
	{
	}

	// DxLibのVECTORとの変換関数
	// cppで実装できなかった
	operator VECTOR() const
	{
		return VGet(x, y, 0.0f);
	}

	bool operator==(Vector2& right) const
	{
		// XとYどちらも同じ値ならtrueを返す
		return (x == right.x && y == right.y);
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

	void operator*=(const float& right)
	{
		x *= right;
		y *= right;
	}

	Vector2 operator/(const float& other)
	{
		// 一回でも割り算を減らす
		// 意味があるのかは知らん！
		float factor = 1 / other;

		Vector2 result;
		result.x = x * factor;
		result.y = y * factor;
		return result;
	}

	Vector2 operator*(const float& other) const
	{
		Vector2 result;
		result.x = x * other;
		result.y = y * other;
		return result;
	}

	Vector2 operator+(const Vector2& other)
	{
		Vector2 result;
		result.x = x + other.x;
		result.y = y + other.y;
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

	Vector2 operator-(const Vector2& other)
	{
		Vector2 result;
		result.x = x - other.x;
		result.y = y - other.y;
		return result;
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
	virtual float SqrMagnitude() const
	{
		return x * x + y * y;
	}

	/// <summary>
	///  大きさ返す
	/// </summary>
	/// <returns>大きさ</returns>
	float Magnitude() const
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
	Vector2 GetNormalize() const
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

	/// <summary>
	/// 補完した後のベクトルを返すのではなく、
	/// startに足したら補完になるベクトルを返す
	/// </summary>
	static Vector2 LerpValue(const Vector2& start, const Vector2& end, const float& rate)
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
		return (end - start) * clampRate;
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

	// 内積
	float Dot(const Vector2& second) const
	{
		return x * second.x + y * second.y;
	}

	// X正方向を始線とした角度
	// Yが下向き正なので時計回りが正の角度になる
	// ゼロベクトルが0度になるのは仕様
	float Angle() const
	{
		float rad = atan2(y, x);
		if (rad < 0)
		{
			rad += Calculation::kPi * 2;
		}
		return rad * Calculation::kRadToDeg;
	}

	// 引数に入れられたベクトルとのなす角を出す(度数)
	// 時計回りがプラス、反時計回りがマイナス
	float RerativeAngle(const Vector2& other) const
	{
		float myDeg = this->Angle();
		float otherDeg = other.Angle();
		return myDeg - otherDeg;
	}

	// 自信を時計回りにdeg度回したベクトルを返す
	// 今回は三角関数を使うが、いずれ行列かクオータニオンを使いたい
	// sqrtを使っているので重たいよ
	Vector2 RotatedVec(const float& deg) const
	{
		Vector2 rotatedVec;
		float myAngle = Angle();
		float mySize = Magnitude();
		rotatedVec.x = mySize * cosf((myAngle + deg) * Calculation::kDegToRad);
		rotatedVec.y = mySize * sinf((myAngle + deg) * Calculation::kDegToRad);
		return rotatedVec;
	}
};

/// <summary>
/// Not a Vector
/// 違いは、有効かどうか尋ねられたら必ずfalseを返すこと
/// 計算で、返すVectorが解なしになったときとかに渡す
/// </summary>
struct NaV : public Vector2
{
	NaV() : Vector2(false){}

	// ダウンキャスト用
	explicit NaV(Vector2) : Vector2(false) {};

	float SqrMagnitude() const override
	{
		return std::numeric_limits<float>::quiet_NaN();
	}
};

/// <summary>
/// int型として使うデータ、でも二つ一緒にして扱いたい…！
/// そんなあなたに
/// 基本的な算術演算子のみ対応
/// 決して浮動小数点にはならず、切り捨てられるので注意
/// </summary>
struct Vector2Int
{
	int x;
	int y;

	Vector2Int() : x(0), y(0) {}

	Vector2Int(const int& _x, const int& _y) : x(_x), y(_y) {}

	Vector2Int(const int& value) : x(value), y(value) {}

	// Vector2への変換関数
	operator Vector2()
	{
		return Vector2(static_cast<float>(x), static_cast<float>(y));
	}

	operator const Vector2() const
	{
		return Vector2(static_cast<float>(x), static_cast<float>(y));
	}

	void operator+=(const Vector2Int& right)
	{
		x += right.x;
		y += right.y;
	}

	void operator-=(const Vector2Int& right)
	{
		x -= right.x;
		y -= right.y;
	}

	void operator*=(const int& right)
	{
		x *= right;
		y *= right;
	}

	Vector2Int operator*(const int& right)
	{
		return Vector2Int(x * right, y * right);
	}

	void operator/=(int right)
	{
		x /= right;
		y /= right;
	}

	Vector2Int operator/(const int& right)
	{
		return Vector2Int(x / right, y / right);
	}
};