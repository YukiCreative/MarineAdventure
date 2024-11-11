#pragma once
#include "Vector2.h"
#include <memory>
#include <array>

class MapChip;
class Player;

/// <summary>
/// マップチップを並べる、
/// マップチップを動かす、
/// マップチップを適切に読み込む、
/// マップチップを必要な分だけ表示する
/// </summary>
class MapSystem
{
private:
	std::array<std::shared_ptr<MapChip>, 17*10> m_mapChips;

	/// <summary>
	/// マップチップの表示位置をずらす
	/// </summary>
	/// <param name="moveValue">現在の位置からどれだけ移動させるか</param>
	void MoveMap(Vector2 moveValue);
public:
	MapSystem();

	/// <summary>
	/// 現在の描画場所に応じて表示するマップチップを判断
	/// </summary>
	void Update(std::shared_ptr<Player> player);
	/// <summary>
	/// マップチップを描画
	/// </summary>
	void Draw();
};

