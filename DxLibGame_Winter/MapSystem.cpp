#include "MapSystem.h"
#include <DxLib.h>
#include <cassert>
#include "game.h"
#include "MapChip.h"
#include "MapImageStore.h"
#include "Player.h"

namespace
{
	// マップチップ同士の間隔
	constexpr int kChipSpace = 80;
	// 今後変数にするかも
	constexpr int kWidthChipNum = 16 + 1;
	constexpr int kHeightChipNum = 9 + 1;
}

MapSystem::MapSystem()
{
	// マップチップのメモリ確保
	for (auto& chip : m_mapChips)
	{
		chip = std::make_shared<MapChip>();
	}
	// チップを等間隔で配置する
	for (int y = 0; y < kHeightChipNum; ++y)
	{
		for (int x = 0; x < kWidthChipNum; ++x)
		{
			m_mapChips[kWidthChipNum * y + x]->
				Move(Vector2(kChipSpace * x - kChipSpace * 0.5f, kChipSpace * y - kChipSpace * 0.5f));
		}
	}
}

void MapSystem::Update(std::shared_ptr<Player> player)
{
	// 相対的にプレイヤーが動いているように見せる
	MoveMap(player->GetVel() * -1);

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
