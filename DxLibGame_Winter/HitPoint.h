#pragma once
#include <algorithm>

// ‘Ì—Í‚ªint‚È‚Ì‚ª‚İ‚¶‚ß‚È‚Ì‚Å
struct HitPoint
{
private:
	const int kMinHitPoint = 0;
	const int kMaxHitPoint = 99;

	int m_value;
public:
	HitPoint(int value)
	{
		// ’l‚ğ³‚µ‚¢”ÍˆÍ‚Éû‚ß‚é
		m_value = std::clamp(value, kMinHitPoint, kMaxHitPoint);
	}

	void operator=(HitPoint right)
	{
		m_value = right.m_value;
	}

	int Value() const
	{
		return m_value;
	}

	HitPoint operator+(HitPoint right)
	{
		return HitPoint(m_value + right.m_value);
	}

	HitPoint operator-(HitPoint right)
	{
		return HitPoint(m_value - right.m_value);
	}

	void Increase(const HitPoint& value)
	{
		// ‚±‚Ì‘‚«•û•|‚¢‚ñ‚¾‚¯‚Ç
		*this = *this + value;
	}

	void Decrease(const HitPoint& value)
	{
		*this = *this - value;
	}
};