#pragma once
#include "Vector2.h"

/// <summary>
/// いろんな雑計算を集めて置きたいかな
/// </summary>
namespace Geometry
{
	// 点と、線分の最近傍点を返す
	Vector2 GetSegmentIntercept(Vector2 pos, Vector2 first, Vector2 second)
	{
		Vector2 startToEnd = second - first;
		// 正規化
		Vector2 startToEndN = startToEnd.GetNormalize();
		Vector2 endToStartN = Vector2(first - second).GetNormalize();
		Vector2 startToPos = pos - first;
		Vector2 endToPos = pos - second;
		// 始点からposの内積が鈍角なら、最近傍点は始点
		if (startToEndN.Dot(startToPos) < 0)
		{
			return first;
		}
		// 終点からposが鈍角の時、最近傍点は終点
		else if (endToStartN.Dot(endToPos) < 0)
		{
			return second;
		}
		else
		{
			return first + startToEndN * startToEndN.Dot(startToPos);
		}
	}

	// 点と、二点を通る直線の最近傍点を返す
	Vector2 GetLineIntercept(Vector2 pos, Vector2 first, Vector2 second)
	{
		// 正規化
		Vector2 startToEndN = (second - first).GetNormalize();
		Vector2 startToPos = pos - first;
		return first + startToEndN * startToEndN.Dot(startToPos);
	}
}

// 別名を宣言
namespace geo = Geometry;