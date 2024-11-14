#include "MapChip.h"
#include <DxLib.h>
#include "game.h"
#include "MapImageStore.h"
#include "BoxCollider.h"
#include "Camera.h"

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
	Vector2 screenPos = m_camera->Capture(m_pos);
	// x座標が動いていなければｘ、ｙならｙの判定をスキップする
	bool isLoop = false;
	if (screenPos.x <= -kChipOffset && m_movePos.x != 0.0f)
	{
		// カメラのおかげでこんなに簡単な式に！
		m_pos.x += Game::kScreenWidth + kChipOffset;
		isLoop = true;
	}
	if (screenPos.y <= -kChipOffset && m_movePos.y != 0.0f)
	{
		m_pos.y += Game::kScreenHeight + kChipOffset;
		isLoop = true;
	}
	return isLoop;
}

bool MapChip::CheckLoopDownAndRight()
{
	// スクリーン座標を計算
	Vector2 screenPos = m_camera->Capture(m_pos);
	// x座標が動いていなければｘ、ｙならｙの判定をスキップするのはこちらも同じ
	bool isLoop = false;
	if (screenPos.y >= Game::kScreenHeight + kChipOffset && m_movePos.y != 0.0f)
	{
		m_pos.y -= Game::kScreenHeight + kChipOffset;
		isLoop = true;
	}
	if (screenPos.x >= Game::kScreenWidth + kChipOffset && m_movePos.x != 0.0f)
	{
		m_pos.x -= Game::kScreenWidth + kChipOffset;
		isLoop = true;
	}
	return isLoop;
}

MapChip::MapChip(std::shared_ptr<Camera> camera) :
	m_graphHandle(-1)
{
	m_camera = camera;
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
		printf("ループ！！");
	}

	// movePosを0,0でリセット
	m_movePos = Vector2();
}

void MapChip::Draw()
{
	Vector2 drawPos = m_camera->Capture(m_pos);
	DrawRotaGraph(drawPos.x, drawPos.y, kExRate, 0, m_graphHandle, true);
}
