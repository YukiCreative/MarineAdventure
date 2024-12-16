#include "ScreenFade.h"
#include <DxLib.h>
#include "game.h"
#include <cassert>

namespace
{
	constexpr float kAlphaMax = 255;
}

ScreenFade::ScreenFade() :
	m_fadeFrame(0),
	m_transParFrame(0),
	m_color(0x000000),
	m_updateState(&ScreenFade::NormalUpdate)
{
}

ScreenFade& ScreenFade::Getinstance()
{
	static ScreenFade instance;
	return instance;
}

void ScreenFade::Update()
{
	// FadeInかOutかはたまた…
	(this->*m_updateState)();
}

void ScreenFade::FadeInUpdate()
{
	// 終了条件が 現在透明度 > 最終透明度
	m_alpha += m_transParFrame;
	if (m_alpha > m_targetAlpha)
	{
		m_alpha = m_targetAlpha;
		m_updateState = &ScreenFade::NormalUpdate;
		return;
	}
}

void ScreenFade::FadeOutUpdate()
{
	// 終了条件が 現在透明度 < 最終透明度
	m_alpha += m_transParFrame;
	if (m_alpha < m_targetAlpha)
	{
		m_alpha = m_targetAlpha;
		m_updateState = &ScreenFade::NormalUpdate;
		return;
	}
}

void ScreenFade::NormalUpdate()
{
	// 何もしない？
}

void ScreenFade::Draw() const
{
	// Imageを使うか考え中
	SetDrawBlendMode(DX_BLENDMODE_MULA, static_cast<int>(m_alpha.value));
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, m_color, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void ScreenFade::Fade(int totalFrame, int targetPercent)
{
	// 0フレームなら怒る
	assert(totalFrame && "0フレームのフェード　意味ないよ");
	m_targetAlpha = targetPercent / kAlphaMax;
	// m_transPerFrameを割り出す
	m_transParFrame = (m_alpha - m_targetAlpha) / totalFrame;
	// 現在の状態がフェードインかアウトか見る
	// これ関数分けたほうがいいかも
	if (m_transParFrame > 0)
	{
		m_updateState = &ScreenFade::FadeOutUpdate;
	}
	else
	{
		m_updateState = &ScreenFade::FadeInUpdate;
	}
}