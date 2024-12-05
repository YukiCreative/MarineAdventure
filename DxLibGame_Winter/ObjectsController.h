#pragma once
#include <memory>
#include <vector>
#include <list>
#include <unordered_map>
#include "Vector2.h"
#include "ObjectKind.h"

class HarmFish;
class Player;
class Camera;
class GameObject;

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

	// Enemyの生成を列挙体から連想できるように関数を紐づける
	using ObjectFactory_t = std::shared_ptr<GameObject>(ObjectsController::*)(Vector2 pos);
	std::shared_ptr<GameObject> CreateHarmFish(Vector2 spawnPos);
	std::unordered_map<ObjectKind, ObjectFactory_t> m_factoryMap;
public:
	ObjectsController(Player& player, Camera& camera);

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
	/// <summary>
	/// 配列にある敵を削除する
	/// とはいってもアドレスを知っているのは本人だけだけど
	/// </summary>
	/// <param name="deleteEnemy">削除するEnemyのスマポ</param>
	void DespawnEnemy(GameObject* deleteEnemy);
};