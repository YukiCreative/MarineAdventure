#pragma once
#include <cstdint>
#include <memory>
#include <algorithm>

// 0~100�ɐ������ꂽ������float
struct Alpha
{
	const float kMinValue = 0;
	const float kMaxValue = 100;
	float value;
	Alpha() : value(0) {}
	Alpha(float _value)
	{
		value = std::clamp(_value, kMinValue, kMaxValue);
	}
	Alpha(const Alpha& right) : value(right.value) {}
	void operator=(const Alpha& right) { value = right.value; }
	// ���S�Ɍ�����float��(�������ǂ����͕�����Ȃ�)
	operator float() { return value; }
	void operator+=(const float& right)
	{
		*this = *this + right;
	}
	void operator-=(const float& right)
	{
		*this = *this - right;
	}
};

class ScreenFade
{
private:
	// �ǂꂾ�����Ԃ����邩
	int m_fadeFrame;
	// 1�t���[���ɂǂꂾ�������x��ς��邩
	float m_transParFrame;
	// �`��̍��̓����x 0~100%
	Alpha m_alpha;
	// �ڎw�������x
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
	/// �t�F�[�h
	/// </summary>
	/// <param name="totalFrame">�t�F�[�h�ɗv���鎞��</param>
	/// <param name="percent">�ŏI�I�ȓ����x(�S����)</param>
	void Fade(const int& totalFrame, const float& percent);
	void SetColor(const unsigned int& value) { m_color = value; }
};

