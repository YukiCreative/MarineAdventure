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

MapSystem::MapSystem(Camera& camera, ObjectsController& cont, std::string path)
{
	// マップデータを初期化
	m_mapData = std::make_shared<MapDataStore>(path.c_str());

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

bool MapSystem::GetMapChipNotCollidable(const Vector2Int& mapPos) const
{
	// こちら側でマップの端ではfalseを返すように気を遣う
	// MapData持ってるのはこのクラスだし
	Vector2Int mapsize = m_mapData->GetMapSize();
	if (mapPos.x < 0 ||
		mapPos.y < 0 ||
		mapPos.x > mapsize.x ||
		mapPos.y > mapsize.y)
	{
		return false;
	}
	return m_mapData->GetMapData(mapPos).graphHandle == -1;
}

MapChipData MapSystem::GetMapChipData(const Vector2Int& mapPos) const
{
	return  m_mapData->GetMapData(mapPos);
}

Vector2Int MapSystem::GetMapSize()
{
	// 右から左へ受け流す
	return m_mapData->GetMapSize();
}

void MapSystem::MoveMap(Vector2 moveValue)
{
	// 全員の座標を等しくずらしてあげる
	for (auto& chip : m_mapChips)
	{
		chip->Move(moveValue);
	}
}
