#pragma once
#include "Vector2.h"
#include <memory>
#include <array>
#include <list>
#include <vector>
#include "MapConstants.h"
#include "MapDataStore.h"
#include "ObjectKind.h"

class kMapChip;
class Player;
class Camera;
class ObjectsController;

using MapArray_t = std::array<std::shared_ptr<kMapChip>, MapConstants::kWidthChipNum* MapConstants::kHeightChipNum>;
using MapList_t  = std::list <std::shared_ptr<kMapChip>>;

struct ObjectAppearanceStatus
{
	bool isExist;
	// 消えてからのフレーム
	int frameDisappear;
	// 消えてから何フレーム後に再出現できるか
	int spawnSpan;

	ObjectAppearanceStatus();
	ObjectAppearanceStatus(const ObjectKind& spanKind);

	void IncreaseFrame() { ++frameDisappear; }

	// デスポーンしたときに実行してね
	void Despawn() { frameDisappear = -spawnSpan; }

	bool CanSpawn() const
	{
		// 出現していなくて、消えてから十分に経過した
		return !isExist && frameDisappear > 0;
	}
};

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

	// 今のマップにあるオブジェクトが出現しているかどうかを記憶
	// 何もおいてないマスも要素に入れる
	// ここに置いていいかは分からない
	std::vector<ObjectAppearanceStatus> m_isObjectsExist;

	/// <summary>
	/// マップチップの表示位置をずらす
	/// </summary>
	/// <param name="moveValue">現在の位置からどれだけ移動させるか</param>
	void MoveMap(Vector2 moveValue);

	void ResetObjectSpawnStatus();
public:
	MapSystem(Camera& camera, ObjectsController& cont, std::string path);

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
	MapArray_t& GetAllMapChips() { return m_mapChips; }

	// マップチップの中から、壁になってる奴だけ取得
	MapList_t& GetCollidableMapChips();

	// 与えられたマップ座標が壁かどうかを返す
	bool GetMapChipCollidable(const Vector2Int& mapPos) const;

	MapChipData GetMapChipData(const Vector2Int& mapPos) const;
	Vector2Int GetMapSize() const;

	// 読み取りなおす
	void ChangeMapData(const std::string& path);

	// オブジェクト出現状況を取得
	bool CanSpawnObject(const Vector2Int& mapPos) const;

	// デスポーンしたときに呼ぶ
	// やっぱこれObjectControllerに持たせるべきでは
	void Despawned(const Vector2Int& mapPos);
};

