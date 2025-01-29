#pragma once
#include "ObjectKind.h"
#include "Vector2.h"
#include <functional>
#include <list>
#include <memory>
#include <unordered_map>
#include <vector>

class HarmFish;
class Player;
class Camera;
class GameObject;
class MapSystem;
class GameEffect;
class Enemy;

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

	void Spawn()
	{
		isExist = true;
	}

	// デスポーンしたときに実行してね
	void Despawn() 
	{
		frameDisappear = -spawnSpan;
		isExist = false;
	}

	bool CanSpawn() const
	{
		// 出現していなくて、消えてから十分に経過した
		return !isExist && frameDisappear >= 0;
	}
};

/// <summary>
/// シーンでこれをインスタンス化して
/// 管理してもらう
/// </summary>
class ObjectsController
{
private:
	// Enemyに渡すため
	Player& m_playerRef;
	Camera& m_cameraRef;

	using ObjectList_t = std::list<std::shared_ptr<GameObject>>;
	ObjectList_t m_objects;

	// オブジェクトの生成を列挙体から連想できるように関数を紐づける
	using ObjectFactory_t = std::function<std::shared_ptr<GameObject>(const Vector2& spawnPos, const Vector2Int& baseMapPos)>;
	std::unordered_map<ObjectKind, ObjectFactory_t> m_factoryMap;

	// スポーン操作関連
	// 今のマップにあるオブジェクトの出現状況を記憶
	std::vector<ObjectAppearanceStatus> m_isObjectsExist;
	Vector2Int m_mapSize;

	void AvoidOverlappingEnemies();
public:
	ObjectsController(Camera& camera, Player& player);

	void Update();
	void DrawFrontMapObject() const;
	void DrawBehindMapObject() const;

	/// <summary>
	/// 種類と位置を指定してくれればこちらで生成いたします
	/// </summary>
	void SpawnObject(const ObjectKind& kind, const Vector2& spawnPos, const Vector2Int& baseMapPos);
	/// <summary>
	/// インスタンス渡してもいいよ
	/// </summary>
	void SpawnObject(std::shared_ptr<GameObject> objectInstance);
	
	void ClearObjects();

	// このクラスからアクセスしたい、MapSytemのメンバを使う処理というね
	void ResetObjectSpawnStatus(MapSystem& system);
	bool CanSpawnObject(const Vector2Int& mapPos) const;
	void Despawned(const Vector2Int& mapPos);
};