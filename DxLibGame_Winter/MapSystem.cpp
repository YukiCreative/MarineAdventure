#include "MapSystem.h"
#include <DxLib.h>
#include <cassert>
#include "game.h"
#include "MapChip.h"
#include "MapImageStore.h"
#include "Camera.h"
#include "MapConstants.h"
#include "ObjectsController.h"
#include "MapDataStore.h"
#include <unordered_map>

namespace
{
	// これわメンバ変数にしたほうがよさそうだなあ しないけど
	std::unordered_map<ObjectKind, int> spawnSpanMap =
	{
		// 再出現のクールタイムがあるのは、たくさん出現して、動くやつ
		{ObjectKind::kEmpty, 0},
		{ObjectKind::kHarmFish, Game::kFrameRate * 60},
		{ObjectKind::kBoss,  0},
		{ObjectKind::kDoor1, 0},
		{ObjectKind::kDoor2, 0},
		{ObjectKind::kDoor3, 0},
		{ObjectKind::kDoor4, 0},
		{ObjectKind::kDoor5, 0},
		{ObjectKind::kDoor6, 0},
		{ObjectKind::kDoor7, 0},
		{ObjectKind::kDoor8, 0},
	};
}

MapSystem::MapSystem(Camera& camera, ObjectsController& cont, std::string path)
{
	// マップデータを初期化
	m_mapData = std::make_shared<MapDataStore>(path.c_str());

	ResetObjectSpawnStatus();

	// マップチップのメモリ確保
	// マップの初期位置を設定
	for (int y = 0; y < MapConstants::kHeightChipNum; ++y)
	{
		for (int x = 0; x < MapConstants::kWidthChipNum; ++x)
		{
			auto& chip = m_mapChips[MapConstants::kWidthChipNum * y + x];
			chip = std::make_shared<kMapChip>(camera, cont,
				Vector2(MapConstants::kChipSize * x - Game::kScreenWidth * 0.5f,
						MapConstants::kChipSize * y - Game::kScreenHeight * 0.5f),
				Vector2Int(x,y), *this);
		}
	}
}

void MapSystem::Update()
{
	for (auto& chip : m_mapChips)
	{
		chip->Update();
	}

	for (auto& status : m_isObjectsExist)
	{
		// タイマー加算
		status.IncreaseFrame();
	}
}

void MapSystem::Draw()
{
	for (auto& chip : m_mapChips)
	{
		chip->Draw();
	}
}

MapList_t& MapSystem::GetCollidableMapChips()
{
	// 壁として有効なチップだけピックする
	m_collidableMapChips.clear();
	for (const auto& chip : m_mapChips)
	{
		if (chip->CanCollide())
		{
			m_collidableMapChips.push_back(chip);
		}
	}

	// 現在の画面内の壁の数
	//printf("%d\n", static_cast<int>(m_collidableMapChips.size()));

	return m_collidableMapChips;
}

bool MapSystem::GetMapChipCollidable(const Vector2Int& mapPos) const
{
	// こちら側でマップの端ではfalseを返すように気を遣う
	// MapData持ってるのはこのクラスだし
	Vector2Int mapsize = m_mapData->GetMapSize();
	if (mapPos.x < 0 ||
		mapPos.y < 0 ||
		mapPos.x > mapsize.x ||
		mapPos.y > mapsize.y)
	{
		return true;
	}
	return m_mapData->GetMapData(mapPos).graphHandle != -1;
}

MapChipData MapSystem::GetMapChipData(const Vector2Int& mapPos) const
{
	return  m_mapData->GetMapData(mapPos);
}

Vector2Int MapSystem::GetMapSize() const
{
	// 右から左へ受け流す
	return m_mapData->GetMapSize();
}

void MapSystem::ChangeMapData(const std::string& path)
{
	m_mapData->LoadMapData(path);

	ResetObjectSpawnStatus();

	// マップチップを再読み込み
	// 別の関数に切り離してもいいかも
	for (auto& chip : m_mapChips)
	{
		chip->ResetMapData();
	}
}

bool MapSystem::CanSpawnObject(const Vector2Int& mapPos) const
{
	// 条件
	// そいつが今出現していなくて、かつ消えてから再出現可能な秒数経っていたら
	ObjectAppearanceStatus status = m_isObjectsExist[mapPos.x + GetMapSize().x * mapPos.y];
	return status.CanSpawn();
}

void MapSystem::Despawned(const Vector2Int& mapPos)
{
	m_isObjectsExist[mapPos.x + GetMapSize().x * mapPos.y].Despawn();
}

void MapSystem::MoveMap(Vector2 moveValue)
{
	// 全員の座標を等しくずらしてあげる
	for (auto& chip : m_mapChips)
	{
		chip->Move(moveValue);
	}
}

void MapSystem::ResetObjectSpawnStatus()
{
	// マップチップの数だけ初期化
	m_isObjectsExist.resize(GetMapSize().x * GetMapSize().y);

	// 範囲for使えなかった
	for (int i = 0; i < m_isObjectsExist.size(); ++i)
	{
		m_isObjectsExist[i] = ObjectAppearanceStatus(m_mapData->GetObjKind(i));
	}
}

// ==============================================================================

ObjectAppearanceStatus::ObjectAppearanceStatus() :
	spawnSpan(spawnSpanMap[ObjectKind::kEmpty]),
	frameDisappear(0),
	isExist(false)
{
}

ObjectAppearanceStatus::ObjectAppearanceStatus(const ObjectKind& spanKind) :
	spawnSpan(spawnSpanMap[spanKind]),
	frameDisappear(0),
	isExist(false)
{
}