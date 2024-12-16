#pragma once
#include <cstdint>
#include <memory>
#include <algorithm>

// 0~255に制限されたただのfloat
struct Alpha
{
	const float kMinValue = 0;
	const float kMaxValue = 255;
	float value;
	Alpha() : value(0) {}
	Alpha(float _value)
	{
		value = std::clamp(_value, kMinValue, kMaxValue);
	}
	Alpha(const Alpha& right) : value(right.value) {}
	void operator=(const Alpha& right) { value = right.value; }
	// 完全に見た目floatに(いいかどうかは分からない)
	operator float() { return value; }
	void operator+=(Alpha& right)
	{
		*this = *this + right;
	}
	void operator-=(Alpha& right)
	{
		*this = *this - right;
	}
};

class ScreenFade
{
private:
	// どれだけ時間かけるか
	int m_fadeFrame;
	// 1フレームにどれだけ透明度を変えるか
	Alpha m_transParFrame;
	// 描画の今の透明度 0~255
	Alpha m_alpha;
	// 目指す透明度
	Alpha m_targetAlpha;
	unsigned int m_color;

	using UpdateState_t = void (ScreenFade::*)();
	UpdateState_t m_updateState;
private:
	ScreenFade();
	ScreenFade(const ScreenFade&) = delete;
	void operator=(const ScreenFade&) = delete;

	void FadeInUpdate();
	void FadeOutUpdate();
	void NormalUpdate();
public:
	static ScreenFade& Getinstance();

	void Update();
	void Draw() const;
	/// <summary>
	/// フェード
	/// </summary>
	/// <param name="totalFrame">フェードに要する時間</param>
	/// <param name="percent">最終的な透明度(百分率)</param>
	void Fade(int totalFrame, int percent);
	void SetColor(const unsigned int& value) { m_color = value; }
};

