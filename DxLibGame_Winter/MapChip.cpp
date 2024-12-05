#include "MapChip.h"
#include <DxLib.h>
#include "game.h"
#include "BoxCollider.h"
#include "Camera.h"
#include "MapConstants.h"
#include "ObjectsController.h"
#include "MapSystem.h"
#include "Player.h"
#include "MapImageStore.h"

void MapChip::ResetMapData()
{
	// マップデータに問い合わせてマップ情報をもらう
	ObjectKind objKind;
	m_system.GetMapChipData(m_mapPos, m_graphHandle, objKind);
	m_objectsController.SpawnObject(objKind, m_pos);
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
		m_mapPos.x += MapConstants::kWidthChipNum;
		isLoop = true;
	}
	if (screenPos.y <= -MapConstants::kChipOffset) // 上から下へ
	{
		m_pos.y += Game::kScreenHeight + MapConstants::kChipOffset * 2;
		m_mapPos.y += MapConstants::kHeightChipNum;
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
		m_mapPos.y -= MapConstants::kHeightChipNum;
		isLoop = true;
	}
	if (screenPos.x >= Game::kScreenWidth + MapConstants::kChipOffset) // 右端から左端へ
	{
		m_pos.x -= Game::kScreenWidth + MapConstants::kChipOffset * 2;
		m_mapPos.x -= MapConstants::kWidthChipNum;
		isLoop = true;
	}
	return isLoop;
}

MapChip::MapChip(Camera& camera, ObjectsController& cont, const Vector2 initPos, const Vector2Int initMapPos, MapSystem& system) :
	GameObject(initPos),
	m_graphHandle(-1),
	m_camera(camera),
	m_objectsController(cont),
	m_mapPos(initMapPos),
	m_system(system)
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
		printf("MapPos:x=%d,y=%d\n", m_mapPos.x, m_mapPos.y);
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

bool MapChip::CanCollide() const
{
	return m_graphHandle != -1;
}

void MapChip::ChangeGraph_Debug()
{
	m_graphHandle = MapImageStore::GetInstance().GetGraph(158);
}
