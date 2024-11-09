#include "MapSystem.h"
#include <DxLib.h>
#include <cassert>
#include "game.h"
#include "MapChip.h"
#include "MapImageStore.h"

namespace
{
	// マップチップ同士の間隔
	constexpr int kChipSpace = 32;
	// 今後変数にするかも
	constexpr int kWidthChipNum = Game::kScreenWidth / kChipSpace;
	constexpr int kHeightChipNum = Game::kScreenHeight / kChipSpace;
}

MapSystem::MapSystem() :
	m_widthChipNum(kWidthChipNum),
	m_heightChipNum(kHeightChipNum),
	m_mapPos()
{
	// マップチップのメモリ確保
	for (auto& chip : m_mapChips)
	{
		chip = std::make_shared<MapChip>();
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

void MapSystem::MoveMap(Vector2 moveValue)
{
	// 全員の座標を等しくずらしてあげる
	for (auto& chip : m_mapChips)
	{
		
	}
}
