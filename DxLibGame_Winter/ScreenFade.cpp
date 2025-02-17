#include "ScreenFade.h"
#include <DxLib.h>
#include "game.h"
#include <cassert>

namespace
{
	constexpr float kAlphaMax = 255.0f;
	constexpr float kPercentToBlendParam = 255.0f / 100.0f;
}

ScreenFade::ScreenFade() :
	m_fadeFrame(0),
	m_transParFrame(0),
	m_color(0x000000),
	m_updateState(&ScreenFade::NormalUpdate),
	m_alpha(100),
	m_isFading(false)
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
	// 透明度を下げる
	// 終了条件が 現在透明度 < 最終透明度
	m_alpha += m_transParFrame;
	if (m_alpha <= m_targetAlpha)
	{
		SetNormalUpdate();
		return;
	}
}

void ScreenFade::FadeOutUpdate()
{
	// 透明度を上げる
	// 終了条件が 現在透明度 > 最終透明度
	m_alpha += m_transParFrame;
	if (m_alpha >= m_targetAlpha)
	{
		SetNormalUpdate();
		return;
	}
}

void ScreenFade::NormalUpdate()
{
	// 何もしない？
}

void ScreenFade::SetNormalUpdate()
{
	m_alpha = m_targetAlpha;
	m_updateState = &ScreenFade::NormalUpdate;
	// フェード止めました
	m_isFading = false;
}

void ScreenFade::Draw() const
{
	// やっぱ乗算合成は幻やったんやなって
	// 乗算使うと白色のフェードができなくなった
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(m_alpha.value * kPercentToBlendParam));
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, m_color, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void ScreenFade::Fade(const int& totalFrame, const float& percent)
{
	// 0フレームなら怒る
	assert(totalFrame && "0フレームのフェード　意味ないよ　すぐにフェードしたいなら1フレームでよろ");
	m_targetAlpha = percent;
	// m_transPerFrameを割り出す
	m_transParFrame = (m_targetAlpha - m_alpha) / totalFrame;
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

	// フェード始めました
	m_isFading = true;
}