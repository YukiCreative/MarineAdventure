#pragma once
#include "Vector2.h"

/// <summary>
/// いろんな雑計算を集めて置きたいかな
/// 11/28注意！ゼロ除算を含む関数があるので、一次関数は使わないでください。これ以上いじらないし
/// </summary>
namespace Geometry
{
	/// <summary>
	/// 無限
	/// 多分要る
	/// </summary>
	struct Inf
	{

	};

	/// <summary>
	/// 一次関数構造体
	/// 傾き、切片を持つ
	/// </summary>
	struct LinearFunction
	{
		const float a = 0.1f;

	public:
		float slope = 0;
		float intercept = 0;
		
		/// <summary>
		/// 二つの点から、それらを通る一次関数を計算
		/// </summary>
		LinearFunction(const Vector2& firstPos, const Vector2& secondPos)
		{
			Vector2 line = secondPos - firstPos;
			slope = Slope(line);
			intercept = Intercept(firstPos, slope);
		}

	private:
		/// <summary>
		/// 現在位置と傾きからワールド座標のｘ軸との切片を求める
		/// </summary>
		float Intercept(const Vector2& pos, const float slope)
		{
			return pos.y - slope * pos.x;
		}
		/// <summary>
		/// 直線の傾きを出します
		/// いいか？引数に入れるのは線としてのベクトルだぞ
		/// 位置ベクトル(原点からのベクトル)は入れると原点からの傾きが出るぞ
		/// </summary>
		float Slope(const Vector2& line)
		{
			// これｘが0なら何か違うものを返さないと…
			return line.y / line.x;
		}
		/// <summary>
		/// 引数で与えられた二つの一次方程式の交点のワールド座標を返します
		/// 平行ならNot a Vector()が返ってきます　返却先で、お手数ですが判定をお願いします
		/// </summary>
		static Vector2 IntersectionOfLines(const LinearFunction& first, const LinearFunction& second)
		{
			Vector2 intersection;
			// 計算量節約のため
			const float slopeSub = first.slope - second.intercept;
			const float slopeSubFactor = 1 / slopeSub;
			// 平行ならなんか良くない値を返したい
			if (slopeSub < 0.000001f) return NaV();
			intersection.x = second.intercept * slopeSubFactor - first.intercept * slopeSubFactor;
			intersection.y = second.slope * first.intercept * -slopeSubFactor - first.slope * second.intercept * -slopeSubFactor;
			return intersection;
		}
	};

	// 点と、線分の最近傍点を返す
	Vector2 GetIntercept(Vector2 pos, Vector2 first, Vector2 second)
	{
		Vector2 startToEnd = second - first;
		// 正規化
		Vector2 startToEndN = startToEnd.GetNormalize();
		Vector2 startToPos = pos - first;
		float t = Vector2::InnerProduct(startToEndN, startToPos);
		// ベクトルが反対方向に向かっていたら
		if (t < 0)
		{
			return first;
		}
		// ベクトルが線分を超えていたら
		if (t * t > VSquareSize(startToEnd))
		{
			return second;
		}
		return first + startToEndN * t;
	}
}

// 別名を宣言
namespace geo = Geometry;