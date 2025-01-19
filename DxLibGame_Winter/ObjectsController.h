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
	using ObjectFactory_t = std::function<std::shared_ptr<GameObject>(Vector2)>;
	std::unordered_map<ObjectKind, ObjectFactory_t> m_factoryMap;
public:
	ObjectsController(Camera& camera, Player& player);

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
};