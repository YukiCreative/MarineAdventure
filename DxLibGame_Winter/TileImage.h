#pragma once
#include "Vector2.h"
#include <string>

// “Á’è‚Ì‰æ‘œ‚ğ•À‚×‚Äo‚µ‚½‚¢‚Æ‚«‚Ég‚¤
class TileImage
{
private:
	int m_handle;
	Vector2Int m_graphSize;
	float m_exRate;
public:
	TileImage(const std::string& fileName);

	void Draw(const Vector2& leftTop, const Vector2& rightBottom) const;

	void SetImage(const std::string& fileName);
	void SetExRate(const float value) { m_exRate = value; }
};

