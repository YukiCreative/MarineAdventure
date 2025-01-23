#pragma once
#include "Vector2.h"
#include <array>

class ImageObject;

namespace
{
	constexpr int kTextNum = 8;
}

// ゲームオーバーのためのテキスト
// もう何も継承しない
class GameoverText
{
private:
	Vector2 m_pos;
	int m_frameCount;

	// 一文字ずつ画像を入れる
	// 予定だったがやめるかも
	std::array<ImageObject, kTextNum> m_gameoverText;
public:
	GameoverText(const Vector2& initPos);

	void Update();
	void Draw() const;
};