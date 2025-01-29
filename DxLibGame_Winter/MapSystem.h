#pragma once
#include "Vector2.h"
#include <memory>
#include <array>
#include <list>
#include <vector>
#include "MapConstants.h"
#include "MapDataStore.h"
#include "ObjectKind.h"

class MapChip;
class Player;
class ObjectsController;

using MapArray_t = std::array<std::shared_ptr<MapChip>, MapConstants::kWidthChipNum* MapConstants::kHeightChipNum>;
using MapList_t  = std::list <std::shared_ptr<MapChip>>;

/// <summary>
/// マップチップを並べる、
/// マップチップを動かす、
/// マップチップを適切に読み込む、
/// マップチップを必要な分だけ表示する
/// </summary>
class MapSystem
{
private:
	MapArray_t m_mapChips;
	// 左辺値が必要とのこと
	MapList_t m_collidableMapChips;
	// 今マップのデータをMapSystemが持つようにしようか考え中
	std::shared_ptr<MapDataStore> m_mapData;

	/// <summary>
	/// マップチップの表示位置をずらす
	/// </summary>
	/// <param name="moveValue">現在の位置からどれだけ移動させるか</param>
	void MoveMap(Vector2 moveValue);
public:
	MapSystem(Camera& camera, std::string path);

	/// <summary>
	/// 現在の描画場所に応じて表示するマップチップを判断
	/// </summary>
	void Update();
	/// <summary>
	/// マップチップを描画
	/// </summary>
	void Draw() const;
	void DrawBackGround() const;
	/// <summary>
	/// マップチップを見せる
	/// </summary>
	/// <returns>マップチップすべて</returns>
	MapArray_t& GetAllMapChips() { return m_mapChips; }

	// マップチップの中から、壁になってる奴だけ取得
	MapList_t& GetCollidableMapChips();

	// 与えられたマップ座標が壁かどうかを返す
	bool GetMapChipCollidable(const Vector2Int& mapPos) const;

	MapChipData GetMapChipData(const Vector2Int& mapPos) const;
	Vector2Int GetMapSize() const;

	// 読み取りなおす
	void ChangeMapData(const std::string& path, ObjectsController& cont);

	// DataStoreの橋渡し
	// 何も悪いことしてないよ
	ObjectKind GetObjKind(const int& index);
	ObjectKind GetObjKind(const Vector2Int& mapPos);
};

