#pragma once
#include <string>
#include "Vector2.h"
#include "Calculation.h"

// 画像を表示するコンポーネントっぽいやつ
class Image
{
private:
	int     m_sourceHandle;
	float   m_expandRate;
	float   m_angle;
	int     m_blendMode;
	uint8_t m_blendPal;
	bool    m_reverceX;
	bool    m_reverceY;
	Vector2 m_offset;
public:
	Image(const int& handle);
	Image(const std::string& path);

	void Draw(const Vector2& pos) const;

	void SetGraph(const int& handle) { m_sourceHandle = handle; }
	void SetGraph(const std::string& path);

	// 現在の何倍の大きさにするか
	void ExpandGraph(const float& exRate) { m_expandRate *= exRate; }
	// 代入
	void SetExRate(const float& value)    { m_expandRate = value; }
	// 現状から何度回転させるか
	void RotateGraph(const float& deg)    { m_angle += deg * Calculation::kDegToRad; }
	// 代入
	void SetAngle(const float& angleDeg)  { m_angle = angleDeg * Calculation::kDegToRad; }
	// SetDrawBlendModeをそのまま表に見せている
	void SetImageBlendMode(const int& blendmode, const int& pal)
	{
		m_blendMode = blendmode;
		m_blendPal = pal;
	}
	void SetImageBlendMode(const int& blendMode) { m_blendMode = blendMode; }
	void SetImageBlendPal (const int& pal)       { m_blendPal = pal; }
	void SetReverceFlagX  (const bool& value)	 { m_reverceX = value; }
	void SetReverceFlagY  (const bool& value)	 { m_reverceY = value; }
	void SetOffset		  (const Vector2& value) { m_offset = value; }
	int GraphHandle() const { return m_sourceHandle; }
	
	const float& ExRate() const { return m_expandRate; }
};

