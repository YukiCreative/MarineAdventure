#include "ScreenEffectController.h"
#include <DxLib.h>
#include "game.h"

// フェードインアウトの処理
ScreenEffectController::ScreenFade::ScreenFade(int frame, float fadePercent, unsigned int color) :
	m_color(color),
	m_lifeFrame(frame),
	m_percent(fadePercent)
{
	// 与えられた情報と今のフェードパネルの透明度から、
	// 位置フレームにどれだけ透明度を操作すればいいのかを割り出す
}

void ScreenEffectController::ScreenFade::Update()
{

}

// ==================================

void ScreenEffectController::Update()
{
	if (m_screenEffects.empty()) return;

	bool isFinished = true;
	for (auto& effect : m_screenEffects.front())
	{
		isFinished &= effect->IsFinished();
	}
	// 今のキューのすべての画像効果が終わったら
	if (isFinished)
	{
		// 取り出す
		m_screenEffects.pop_front();
	}
	// 気を取り直してUpdate
	for (auto& effect : m_screenEffects.front())
	{
		effect->Update();
	}
}

void ScreenEffectController::Draw() const
{
	// ここでFadePanelをDraw
	m_fadePanel->Draw();
}

// ============================

void ScreenEffectController::FadePanel::Draw() const
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_alpha);
	// 画面いっぱいに描画
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, m_color, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
