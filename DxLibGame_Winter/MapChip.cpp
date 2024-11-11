#include "MapChip.h"
#include <DxLib.h>
#include "game.h"
#include "MapImageStore.h"

namespace
{
	constexpr int kChipSize = 80;
	constexpr int kImageSize = 16;
	constexpr float kExRate = static_cast<float>(kChipSize) / static_cast<float>(kImageSize);
	// 現時点でのマップチップの一辺の半分のピクセル
	// DrawRectGraphは画像の中心が原点なのでこうなる
	constexpr int kChipOffset = kChipSize * 0.5f;
}

void MapChip::SetGraph()
{
	// MapImageStoreに問い合わせる
	MapImageStore& mapImageStore = MapImageStore::GetInstance();
	// とりあえず今は固定で
	m_graphHandle = mapImageStore.GetGraph(70);
}

bool MapChip::LoopScreen()
{
	// 自分の座標が特定の範囲外に出てたら
	// 反対側に瞬間移動
	// 上と左方向が優先(でないと1フレームのうちに反復横跳びする)
	// 短絡評価によって実装している
	return CheckLoopUpAndLeft() || CheckLoopDownAndRight();
}

bool MapChip::CheckLoopUpAndLeft()
{
	// x座標が動いていなければｘ、ｙならｙの判定をスキップする
	bool isLoop = false;
	if (m_graphPos.x <= -kChipOffset && m_movePos.x != 0.0f)
	{
		m_graphPos.x = Game::kScreenWidth + kChipOffset - m_movePos.x;
		isLoop = true;
	}
	if (m_graphPos.y <= -kChipOffset && m_movePos.y != 0.0f)
	{
		m_graphPos.y = Game::kScreenHeight + kChipOffset - m_movePos.y;
		isLoop = true;
	}
	return isLoop;
}

bool MapChip::CheckLoopDownAndRight()
{
	// x座標が動いていなければｘ、ｙならｙの判定をスキップするのはこちらも同じ
	bool isLoop = false;
	if (m_graphPos.y >= Game::kScreenHeight + kChipOffset && m_movePos.y != 0.0f)
	{
		m_graphPos.y = -kChipOffset + m_movePos.y;
		isLoop = true;
	}
	if (m_graphPos.x >= Game::kScreenWidth + kChipOffset && m_movePos.x != 0.0f)
	{
		m_graphPos.x = -kChipOffset + m_movePos.x;
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
	// 処理の順序は移動→ループ判定
	m_graphPos += m_movePos;

	bool isLoop = LoopScreen();
	// 瞬間移動が起こったら画像を再取得
	if (isLoop)
	{
		SetGraph();
		//printfDx("ループ！！");
	}

	// movePosを0,0でリセット
	m_movePos = Vector2();
}

void MapChip::Draw()
{
	DrawRotaGraph(m_graphPos.x, m_graphPos.y, kExRate, 0, m_graphHandle, true);
}
