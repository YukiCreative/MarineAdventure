#include "MapChip.h"
#include <DxLib.h>
#include "game.h"
#include "MapImageStore.h"
#include "BoxCollider.h"
#include "Camera.h"
#include "EnemyController.h"
#include "HarmFish.h"

namespace MapConstants
{
	constexpr float kChipSize = 80.0f;
	constexpr int kImageSize = 16;
	constexpr float kExRate = static_cast<float>(kChipSize) / static_cast<float>(kImageSize);
	// 現時点でのマップチップの一辺の半分のピクセル
	// DrawRectGraphは画像の中心が原点なのでこうなる
	constexpr int kChipOffset = static_cast<int>(kChipSize * 0.5f);
}

void MapChip::ResetMapData()
{
	// MapImageStoreに問い合わせる
	MapImageStore& mapImageStore = MapImageStore::GetInstance();
	// とりあえず今は固定で
	m_graphHandle = mapImageStore.GetGraph(rand() % 2);
	// とりあえず確率で敵だしとけばええんちゃう
	//if (!(rand() % 200))
	//{
	//	m_enemys.SpawnEnemy(EnemyKinds::kHarmFish, m_pos);
	//}

	// 今後、ここにマップデータに問い合わせてマップ情報をもらう形にする
	// もらうのは、
	// 1.マップチップのスプライト
	// 2.当たり判定を持っているかどうか
	// 3.敵のスポーンポイントかどうか、どの敵を出すのか　
	// これを実現するために、platinumで各レイヤーの3つの配列を持ってきて、
	// 自分のmapPosで参照する
}

bool MapChip::LoopScreen()
{
	// 自分の座標が特定の範囲外に出てたら
	// 反対側に瞬間移動
	// 上と左方向が優先(でないと1フレームのうちに反復横跳びする)
	// 短絡評価によって実装している
	return CheckLoopUpAndLeft() || CheckLoopDownAndRight(); // Checkとか名前付いてるけどがっつりメンバ変数いじってます。ごめんなさい。
}

bool MapChip::CheckLoopUpAndLeft()
{
	// スクリーン座標を計算
	Vector2 screenPos = m_camera.Capture(m_pos);
	// 画面外判定
	bool isLoop = false;
	if (screenPos.x <= -MapConstants::kChipOffset) // 左から右へ
	{
		// ループの式ってこんなのになるんだ
		m_pos.x += Game::kScreenWidth + MapConstants::kChipOffset * 2;
		m_mapPos.x += 
		isLoop = true;
	}
	if (screenPos.y <= -MapConstants::kChipOffset) // 上から下へ
	{
		m_pos.y += Game::kScreenHeight + MapConstants::kChipOffset * 2;
		isLoop = true;
	}
	return isLoop;
}

bool MapChip::CheckLoopDownAndRight()
{
	// スクリーン座標を計算
	Vector2 screenPos = m_camera.Capture(m_pos);
	bool isLoop = false;
	if (screenPos.y >= Game::kScreenHeight + MapConstants::kChipOffset) // 下から上へ
	{
		m_pos.y -= Game::kScreenHeight + MapConstants::kChipOffset * 2;
		isLoop = true;
	}
	if (screenPos.x >= Game::kScreenWidth + MapConstants::kChipOffset) // 右端から左端へ
	{
		m_pos.x -= Game::kScreenWidth + MapConstants::kChipOffset * 2;
		isLoop = true;
	}
	return isLoop;
}

MapChip::MapChip(Camera& camera, EnemyController& cont) :
	m_graphHandle(-1),
	m_camera(camera),
	m_enemys(cont)
{
	m_collider = std::make_shared<BoxCollider>(m_pos, MapConstants::kChipSize, MapConstants::kChipSize);
	ResetMapData();
}

void MapChip::Update()
{
	// 処理の順序は移動→ループ判定
	m_pos += m_movePos;

	// 瞬間移動を試して、起こったら画像を再取得
	if (LoopScreen())
	{
		ResetMapData();
		//printf("ループ！！");
	}

	// movePosを0,0でリセット
	m_movePos = Vector2();
}

void MapChip::Draw() const
{
	Vector2 drawPos = m_camera.Capture(m_pos);
	DrawRotaGraph(static_cast<int>(drawPos.x), static_cast<int>(drawPos.y), MapConstants::kExRate, 0, m_graphHandle, true);
#if _DEBUG
	DrawCircle(static_cast<int>(drawPos.x), static_cast<int>(drawPos.y), 1, 0xff0000);
#endif
}

void MapChip::SetDebugGraph()
{
	MapImageStore& mapImageStore = MapImageStore::GetInstance();
	m_graphHandle = m_graphHandle = mapImageStore.GetGraph(18);
}