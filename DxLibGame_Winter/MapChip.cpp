#include "MapChip.h"
#include <DxLib.h>
#include "game.h"
#include "MapImageStore.h"
#include "BoxCollider.h"
#include "Camera.h"

namespace
{
	constexpr float kChipSize = 80.0f;
	constexpr int kImageSize = 16;
	constexpr float kExRate = static_cast<float>(kChipSize) / static_cast<float>(kImageSize);
	// 現時点でのマップチップの一辺の半分のピクセル
	// DrawRectGraphは画像の中心が原点なのでこうなる
	constexpr int kChipOffset = static_cast<int>(kChipSize * 0.5f);
}

void MapChip::SetGraph()
{
	// MapImageStoreに問い合わせる
	MapImageStore& mapImageStore = MapImageStore::GetInstance();
	// とりあえず今は固定で
	m_graphHandle = mapImageStore.GetGraph(rand() % 2);
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
	// スクリーン座標を計算
	Vector2 screenPos = m_camera.Capture(m_pos);
	// 画面外判定
	bool isLoop = false;
	if (screenPos.x <= -kChipOffset)
	{
		// ループの式ってこんなのになるんだ
		m_pos.x += Game::kScreenWidth + kChipOffset * 2;
		isLoop = true;
	}
	if (screenPos.y <= -kChipOffset)
	{
		m_pos.y += Game::kScreenHeight + kChipOffset * 2;
		isLoop = true;
	}
	return isLoop;
}

bool MapChip::CheckLoopDownAndRight()
{
	// スクリーン座標を計算
	Vector2 screenPos = m_camera.Capture(m_pos);
	bool isLoop = false;
	if (screenPos.y >= Game::kScreenHeight + kChipOffset)
	{
		m_pos.y -= Game::kScreenHeight + kChipOffset * 2;
		isLoop = true;
	}
	if (screenPos.x >= Game::kScreenWidth + kChipOffset)
	{
		m_pos.x -= Game::kScreenWidth + kChipOffset * 2;
		isLoop = true;
	}
	return isLoop;
}

MapChip::MapChip(Camera& camera) :
	m_graphHandle(-1),
	m_camera(camera)
{
	m_collider = std::make_shared<BoxCollider>(m_pos, kChipSize, kChipSize);
	SetGraph();
}

void MapChip::Update()
{
	// 処理の順序は移動→ループ判定
	m_pos += m_movePos;

	// 瞬間移動を試して、起こったら画像を再取得
	if (LoopScreen())
	{
		SetGraph();
		//printf("ループ！！");
	}

	// movePosを0,0でリセット
	m_movePos = Vector2();
}

void MapChip::Draw()
{
	Vector2 drawPos = m_camera.Capture(m_pos);
	DrawRotaGraph(static_cast<int>(drawPos.x), static_cast<int>(drawPos.y), kExRate, 0, m_graphHandle, true);
#if _DEBUG
	DrawCircle(static_cast<int>(drawPos.x), static_cast<int>(drawPos.y), 1, 0xff0000);
#endif
}
