#include "TimeUI.h"
#include "Statistics.h"
#include <string>

namespace
{
	const std::string kText = "Time %02d:%02d";
	const std::string kFontPath = "Data/Font/07にくまるフォント.otf";
	const std::string kFontName = "07にくまるフォント";
	constexpr int kFontSize = 30;
	constexpr int kThickness = -1;
	const Vector2 kBoxSize = { 200, 50 };
	const Vector2 kTextOffset = { 10, -10 };
}

TimeUI::TimeUI(const Vector2& initPos) :
	GameObject(initPos)
{
	AddFontResourceExA(kFontPath.c_str(), FR_PRIVATE, NULL);

	m_fontHandle = CreateFontToHandle(kFontName.c_str(), kFontSize, kThickness);
}

TimeUI::~TimeUI()
{
	DeleteFontToHandle(m_fontHandle);
	RemoveFontResourceExA("", FR_PRIVATE, NULL);
}

void TimeUI::Update()
{
	// 何もすることがない
}

void TimeUI::Draw() const
{
	// 下に半透明の四角を描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawBox(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y - kBoxSize.y * 0.5f),
		static_cast<int>(m_pos.x + kBoxSize.x), static_cast<int>(m_pos.y + kBoxSize.y * 0.5f), 0xffffff, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	const int minutes = Statistics::GetInstance().ClearTimeMinutes();
	const int seconds = Statistics::GetInstance().ClearTimeSeconds();
	DrawFormatStringToHandle(static_cast<int>(m_pos.x + kTextOffset.x), static_cast<int>(m_pos.y + kTextOffset.y), 0xffffff, m_fontHandle, kText.c_str(), minutes, seconds);
}
