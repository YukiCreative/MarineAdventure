#include "MapSystem.h"
#include <DxLib.h>
#include <cassert>
#include "game.h"
#include "MapChip.h"
#include "MapImageStore.h"
#include "Player.h"
#include "Camera.h"

namespace
{
	// マップチップ同士の間隔
	constexpr int kChipSpace = 80;
	// 今後変数にするかも
	constexpr int kWidthChipNum = 16 + 1;
	constexpr int kHeightChipNum = 9 + 1;
}

MapSystem::MapSystem(Camera& camera, EnemyController& cont)
{
	// マップチップのメモリ確保
	for (auto& chip : m_mapChips)
	{
		chip = std::make_shared<MapChip>(camera, cont);
	}
	// チップを等間隔で配置する
	for (int y = 0; y < kHeightChipNum; ++y)
	{
		for (int x = 0; x < kWidthChipNum; ++x)
		{
			m_mapChips[kWidthChipNum * y + x]->
				Move(Vector2(static_cast<float>(kChipSpace * x) - Game::kScreenWidth * 0.5f,
					static_cast<float>(kChipSpace * y) - Game::kScreenHeight * 0.5f));
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

void MapSystem::MoveMap(Vector2 moveValue)
{
	// 全員の座標を等しくずらしてあげる
	for (auto& chip : m_mapChips)
	{
		chip->Move(moveValue);
	}
}
