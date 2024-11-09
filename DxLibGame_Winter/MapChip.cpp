#include "MapChip.h"
#include <DxLib.h>
#include "game.h"
#include "MapImageStore.h"

namespace
{
	// 現時点でのマップチップの一辺の半分のピクセル
	// DrawRectGraphは画像の中心が原点なのでこうなる
	constexpr int kChipOffset = 16;
}

void MapChip::SetGraph()
{
	// MapImageStoreに問い合わせる
	MapImageStore& mapImageStore = MapImageStore::GetInstance();
	// とりあえず今は固定で
	m_graphHandle = mapImageStore.GetGraph(3);
}

bool MapChip::LoopScreen()
{
	// 自分の座標が特定の範囲外に出てたら
	// 反対側に瞬間移動
	
	// 一周させたか
	bool isLoop = false;
	if (m_graphPos.x < -kChipOffset)
	{
		m_graphPos.x = Game::kScreenWidth + kChipOffset;
		isLoop = true;
	}
	if (m_graphPos.x > Game::kScreenWidth + kChipOffset)
	{
		m_graphPos.x = -kChipOffset;
		isLoop = true;
	}
	if (m_graphPos.y < -kChipOffset)
	{
		m_graphPos.y = Game::kScreenHeight + kChipOffset;
		isLoop = true;
	}
	if (m_graphPos.y > Game::kScreenHeight + kChipOffset)
	{
		m_graphPos.y = -kChipOffset;
		isLoop = true;
	}
	return isLoop;
}

MapChip::MapChip() :
	m_graphHandle(-1)
{
	SetGraph();
}

void MapChip::Update()
{
	m_graphPos.x++;
	m_graphPos.y++;

	bool isLoop = LoopScreen();
	// 瞬間移動が起こったら画像を再取得
	if (isLoop)
	{
		SetGraph();
	}
}

void MapChip::Draw()
{
	DrawRotaGraph(m_graphPos.x, m_graphPos.y, 2.0, 0, m_graphHandle, true);
}
