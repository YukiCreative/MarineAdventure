#pragma once
#include <memory>
#include <vector>
#include <list>
#include <unordered_map>
#include "Vector2.h"
#include "ObjectKind.h"
#include <functional>

class HarmFish;
class Player;
class Camera;
class GameObject;
class MapSystem;

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
/// シーンでこれをインスタンス化して
/// 管理してもらう
/// </summary>
class ObjectsController
{
private:
	// Enemyに渡すため
	Player& m_playerRef;
	Camera& m_cameraRef;
	std::weak_ptr<MapSystem> m_mapSystem;

	using ObjectList_t = std::list<std::shared_ptr<GameObject>>;
	ObjectList_t m_objects;

	// オブジェクトの生成を列挙体から連想できるように関数を紐づける
	using ObjectFactory_t = std::function<std::shared_ptr<GameObject>(Vector2)>;
	std::unordered_map<ObjectKind, ObjectFactory_t> m_factoryMap;

	// スポーン操作関連
	// 今のマップにあるオブジェクトの出現状況を記憶
	std::vector<ObjectAppearanceStatus> m_isObjectsExist;
public:
	ObjectsController(Camera& camera, Player& player, std::weak_ptr<MapSystem> system);

	void Update();
	void Draw();

	/// <summary>
	/// 種類と位置を指定してくれればこちらで生成いたします
	/// </summary>
	void SpawnObject(ObjectKind kind, Vector2 spawnPos);
	/// <summary>
	/// インスタンス渡してもいいよ
	/// </summary>
	void SpawnObject(std::shared_ptr<GameObject> objectInstance);
	
	void ClearObjects();

	void ResetObjectSpawnStatus();
	bool CanSpawnObject(const Vector2Int& mapPos) const;
	void Despawned(const Vector2Int& mapPos);
};