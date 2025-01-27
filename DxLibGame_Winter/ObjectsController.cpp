#include "Boss.h"
#include "Camera.h"
#include "DestructibleBlock.h"
#include "Door.h"
#include "Enemy.h"
#include "GameEffect.h"
#include "HarmFish.h"
#include "MapSystem.h"
#include "ObjectKind.h"
#include "ObjectsController.h"
#include "Player.h"
#include <cassert>
#include <vector>

namespace
{
	// これわメンバ変数にしたほうがよさそうだなあ しないけど
	std::unordered_map<ObjectKind, int> spawnSpanMap =
	{
		// 再出現のクールタイムがあるのは、たくさん出現して、動くやつ
		{ObjectKind::kEmpty, 0},
		{ObjectKind::kHarmFish, Game::kFrameRate * 60},
		{ObjectKind::kBoss,  0},
		{ObjectKind::kDoor1, 0},
		{ObjectKind::kDoor2, 0},
		{ObjectKind::kDoor3, 0},
		{ObjectKind::kDoor4, 0},
		{ObjectKind::kDoor5, 0},
		{ObjectKind::kDoor6, 0},
		{ObjectKind::kDoor7, 0},
		{ObjectKind::kDoor8, 0},
	};
}

ObjectsController::ObjectsController(Camera& camera, Player& player) :
	m_playerRef(player),
	m_cameraRef(camera)
{
	// mapの設定
	// functionってすげー
	m_factoryMap[ObjectKind::kHarmFish] = [&](const Vector2& spawnPos, const Vector2Int& baseMapPos) {return std::make_shared<HarmFish>(*this, m_playerRef, m_cameraRef, spawnPos, baseMapPos); };
	m_factoryMap[ObjectKind::kBoss]     = [&](const Vector2& spawnPos, const Vector2Int& baseMapPos) {return std::make_shared<Boss>    (*this, m_playerRef, m_cameraRef, spawnPos, baseMapPos); };
	m_factoryMap[ObjectKind::kDestructibleBlock] = [&](const Vector2& spawnPos, const Vector2Int& baseMapPos) {return std::make_shared<DestructibleBlock>(m_cameraRef, spawnPos, m_playerRef); };
	m_factoryMap[ObjectKind::kDoor1]    = [&](const Vector2& spawnPos, const Vector2Int& baseMapPos) {return std::make_shared<Door>    (m_playerRef, m_cameraRef, spawnPos, static_cast<int>(ObjectKind::kDoor1)); };
	m_factoryMap[ObjectKind::kDoor2]    = [&](const Vector2& spawnPos, const Vector2Int& baseMapPos) {return std::make_shared<Door>    (m_playerRef, m_cameraRef, spawnPos, static_cast<int>(ObjectKind::kDoor2)); };
	m_factoryMap[ObjectKind::kDoor3]    = [&](const Vector2& spawnPos, const Vector2Int& baseMapPos) {return std::make_shared<Door>    (m_playerRef, m_cameraRef, spawnPos, static_cast<int>(ObjectKind::kDoor3)); };
	m_factoryMap[ObjectKind::kDoor4]    = [&](const Vector2& spawnPos, const Vector2Int& baseMapPos) {return std::make_shared<Door>    (m_playerRef, m_cameraRef, spawnPos, static_cast<int>(ObjectKind::kDoor4)); };
	m_factoryMap[ObjectKind::kDoor5]    = [&](const Vector2& spawnPos, const Vector2Int& baseMapPos) {return std::make_shared<Door>    (m_playerRef, m_cameraRef, spawnPos, static_cast<int>(ObjectKind::kDoor5)); };
	m_factoryMap[ObjectKind::kDoor6]    = [&](const Vector2& spawnPos, const Vector2Int& baseMapPos) {return std::make_shared<Door>    (m_playerRef, m_cameraRef, spawnPos, static_cast<int>(ObjectKind::kDoor6)); };
	m_factoryMap[ObjectKind::kDoor7]    = [&](const Vector2& spawnPos, const Vector2Int& baseMapPos) {return std::make_shared<Door>    (m_playerRef, m_cameraRef, spawnPos, static_cast<int>(ObjectKind::kDoor7)); };
	m_factoryMap[ObjectKind::kDoor8]    = [&](const Vector2& spawnPos, const Vector2Int& baseMapPos) {return std::make_shared<Door>    (m_playerRef, m_cameraRef, spawnPos, static_cast<int>(ObjectKind::kDoor8)); };
}

void ObjectsController::Update()
{
	// 生存者リストを宣言
	// 死んだのを消すより簡単
	ObjectList_t aliveObjects;
	// リストの要素全部Update
	for (auto& object : m_objects)
	{
		object->Update();
		// このオブジェクトがまだ生きてたらリストに入れとく
		if (!object->IsDeleted())
		{
			// ポインタをコピー
			aliveObjects.emplace_back(object);
		}
		else
		{
			Despawned(object->GetBaseMapPos());
		}
	}
	// はみ出た要素は自動的に削除される
	m_objects = aliveObjects;

	for (auto& status : m_isObjectsExist)
	{
		// タイマー加算
		status.IncreaseFrame();
	}
}

void ObjectsController::Draw()
{
	for (auto& enemy : m_objects)
	{
		enemy->Draw();
	}
}

void ObjectsController::SpawnObject(const ObjectKind& kind, const Vector2& spawnPos, const Vector2Int& baseMapPos)
{
	if (kind == ObjectKind::kEmpty) return;
	m_objects.push_back(m_factoryMap[kind](spawnPos, baseMapPos));
	// 出現したことを記憶したい
	m_isObjectsExist[baseMapPos.x + baseMapPos.y * m_mapSize.x].Spawn();
}

void ObjectsController::SpawnObject(std::shared_ptr<GameObject> objectInstance)
{
	m_objects.push_back(objectInstance);
}

void ObjectsController::ClearObjects()
{
	m_objects.clear();
}

bool ObjectsController::CanSpawnObject(const Vector2Int& mapPos) const
{
	// 条件
	// そいつが今出現していなくて、かつ消えてから再出現可能な秒数経っていたら
	// ここで、マップの範囲外だったらfalseを返す
	if (mapPos.x < 0 || mapPos.y < 0 || mapPos.x >= m_mapSize.x || mapPos.y >= m_mapSize.y) return false;

	ObjectAppearanceStatus status = m_isObjectsExist[mapPos.x + m_mapSize.x * mapPos.y];
	return status.CanSpawn();
}

void ObjectsController::Despawned(const Vector2Int& mapPos)
{
	m_isObjectsExist[mapPos.x + m_mapSize.x * mapPos.y].Despawn();
}

void ObjectsController::ResetObjectSpawnStatus(MapSystem& system)
{
	m_mapSize = system.GetMapSize();
	// マップチップの数だけ初期化
	m_isObjectsExist.resize(m_mapSize.x * m_mapSize.y);

	// 範囲for使えなかった
	for (int i = 0; i < m_isObjectsExist.size(); ++i)
	{
		m_isObjectsExist[i] = ObjectAppearanceStatus(system.GetObjKind(i));
	}
}

// =====================================

ObjectAppearanceStatus::ObjectAppearanceStatus() :
	spawnSpan(spawnSpanMap[ObjectKind::kEmpty]),
	frameDisappear(0),
	isExist(false)
{
}

ObjectAppearanceStatus::ObjectAppearanceStatus(const ObjectKind& spanKind) :
	spawnSpan(spawnSpanMap[spanKind]),
	frameDisappear(0),
	isExist(false)
{
}