#pragma once
#include "Vector2.h"
#include <string>

// 特定の画像を並べて出したいときに使う
// 水中の壁はできたが、空ができない
// 結局このクラス使わなかったな
class TileImage
{
private:
	int m_handle;
	Vector2Int m_graphSize;
	float m_exRate;
public:
	TileImage(const std::string& fileName);

	// 座標はスクリーン
	void Draw(const Vector2& leftTop, const Vector2& rightBottom) const;

	void SetImage(const std::string& fileName);
	void SetExRate(const float value) { m_exRate = value; }
};

