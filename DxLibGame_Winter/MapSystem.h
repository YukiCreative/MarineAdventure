#pragma once
#include "Vector2.h"
#include <memory>
#include <array>
#include "MapConstants.h"
#include "MapDataStore.h"
#include "ObjectKind.h"

class MapChip;
class Player;
class Camera;
class ObjectsController;

/// <summary>
/// マップチップを並べる、
/// マップチップを動かす、
/// マップチップを適切に読み込む、
/// マップチップを必要な分だけ表示する
/// </summary>
class MapSystem
{
private:
	using MapArray_t = std::array<std::shared_ptr<MapChip>, MapConstants::kWidthChipNum * MapConstants::kHeightChipNum>;
	MapArray_t m_mapChips;
	// 今マップのデータをMapSystemが持つようにしようか考え中
	std::shared_ptr<MapDataStore> m_mapData;

	/// <summary>
	/// マップチップの表示位置をずらす
	/// </summary>
	/// <param name="moveValue">現在の位置からどれだけ移動させるか</param>
	void MoveMap(Vector2 moveValue);
public:
	MapSystem(Camera& camera, ObjectsController& cont, std::string pass);

	/// <summary>
	/// 現在の描画場所に応じて表示するマップチップを判断
	/// </summary>
	void Update();
	/// <summary>
	/// マップチップを描画
	/// </summary>
	void Draw();
	/// <summary>
	/// マップチップを見せる
	/// </summary>
	/// <returns>マップチップすべて</returns>
	MapArray_t& GetMapCihps() { return m_mapChips; };

	void GetMapChipData(const Vector2Int& mapPos, int& handle, ObjectKind& kind);
	Vector2Int GetMapSize();
};

