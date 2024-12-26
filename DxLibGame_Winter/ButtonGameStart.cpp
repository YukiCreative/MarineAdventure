#include "ButtonGameStart.h"

void ButtonGameStart::NormalUpdate()
{
	// 何もしない
}

void ButtonGameStart::ForcusedUpdate()
{
	// 点滅とかさせたい
}

void ButtonGameStart::Onpressed()
{
	// シーン遷移
}

void ButtonGameStart::Draw() const
{
	// UIだしスクリーン座標で描いてもいいよね？
	m_image->Draw(m_pos);
}
