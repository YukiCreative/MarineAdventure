#include "Boss.h"
#include "Camera.h"
#include "Cloud.h"
#include "DestructibleBlock.h"
#include "Door.h"
#include "DoorStage1ToStage2.h"
#include "DoorStage2ToStage3.h"
#include "DoorStageClear.h"
#include "Enemy.h"
#include "GameEffect.h"
#include "HarmFish.h"
#include "MapSystem.h"
#include "ObjectAttribute.h"
#include "ObjectKind.h"
#include "ObjectsController.h"
#include "Player.h"
#include "SeaUrchin.h"
#include "SmallCoin.h"
#include <cassert>
#include <vector>

namespace
{
	std::unordered_map<ObjectKind, int> spawnSpanMap =
	{
		// 再出現のクールタイム
		// そもそも消えないやつは0に設定してある
		{ObjectKind::kEmpty, 0},
		{ObjectKind::kHarmFish, Game::kFrameRate * 60},
		{ObjectKind::kBoss,  0},
		{ObjectKind::kDestructibleBlock, Game::kFrameRate * 60},
		{ObjectKind::kCloud1, 0},
		{ObjectKind::kCloud2, 0},
		{ObjectKind::kCoin, Game::kFrameRate * 300},
		{ObjectKind::kSeaUrchin, 0},
		{ObjectKind::kDoor1, 0},
		{ObjectKind::kDoor2, 0},
		{ObjectKind::kDoor3, 0},
		{ObjectKind::kDoor4, 0},
		{ObjectKind::kDoor5, 0},
		{ObjectKind::kDoor6, 0},
		{ObjectKind::kDoor7, 0},
		{ObjectKind::kDoor8, 0},
	};

	constexpr int kEnemyOverlapThreshold = 5000;
}

void ObjectsController::AvoidOverlappingEnemies()
{
	using EnemyList_t = std::list<std::shared_ptr<Enemy>>;
	// ここで、敵同士の密着を阻止する(倒せないので)
	EnemyList_t enemyList;
	for (auto& object : m_objects)
	{
		// まず敵かどうかを調べて、敵だけの配列を作る
		if (object->Attribute() != ObjectAttribute::kEnemy) continue;

		enemyList.emplace_back(std::static_pointer_cast<Enemy>(object));
	}
	// 敵同士の距離を総当たり
	// ネスト乙
	for (auto& firstEnemy : enemyList)
	{
		for (auto& secondEnemy : enemyList)
		{
			// 自分とは衝突させない
			// この文がなくてもバグらないが、計算量は減る
			if (firstEnemy == secondEnemy) continue;

			// 距離を測って、一定距離以上近づいたら、離す
			Vector2 rerativeVec = firstEnemy->GetPos() - secondEnemy->GetPos();
			float rerativeLength = rerativeVec.SqrMagnitude();
			if (rerativeLength > kEnemyOverlapThreshold) continue;

			Vector2 rerativeVecN = rerativeVec.GetNormalize();

			// お互い離れる方向に力を加える
			firstEnemy ->AddForce(rerativeVecN);
			secondEnemy->AddForce(-rerativeVecN);
		}
	}
}

ObjectsController::ObjectsController(Camera& camera, Player& player) :
	m_playerRef(player),
	m_cameraRef(camera)
{
	// mapの設定
	// メンバの参照はfunctionしかできないと思ったが、ラムダ式でもできたらしい
	m_factoryMap[ObjectKind::kHarmFish] = [&](const Vector2& spawnPos, const Vector2Int& baseMapPos) {return std::make_shared<HarmFish>(*this, m_playerRef, m_cameraRef, spawnPos, baseMapPos); };
	m_factoryMap[ObjectKind::kBoss]     = [&](const Vector2& spawnPos, const Vector2Int& baseMapPos) {return std::make_shared<Boss>    (*this, m_playerRef, m_cameraRef, spawnPos, baseMapPos); };
	m_factoryMap[ObjectKind::kDestructibleBlock] = [&](const Vector2& spawnPos, const Vector2Int& baseMapPos) {return std::make_shared<DestructibleBlock>(m_cameraRef, m_playerRef, spawnPos, baseMapPos); };
	m_factoryMap[ObjectKind::kCloud1]   = [&](const Vector2& spawnPos, const Vector2Int& baseMapPos) {return std::make_shared<Cloud>   (m_cameraRef, spawnPos, CloudKind::k1); };
	m_factoryMap[ObjectKind::kCloud2]   = [&](const Vector2& spawnPos, const Vector2Int& baseMapPos) {return std::make_shared<Cloud>   (m_cameraRef, spawnPos, CloudKind::k2); };
	m_factoryMap[ObjectKind::kCoin]     = [&](const Vector2& spawnPos, const Vector2Int& baseMapPos) {return std::make_shared<SmallCoin>(m_playerRef, m_cameraRef, spawnPos, *this); };
	m_factoryMap[ObjectKind::kSeaUrchin] = [&](const Vector2& spawnPos, const Vector2Int& baseMapPos) {return std::make_shared<SeaUrchin>(*this, spawnPos, m_cameraRef, m_playerRef, baseMapPos); };
	m_factoryMap[ObjectKind::kDoor1]    = [&](const Vector2& spawnPos, const Vector2Int& baseMapPos) {return std::make_shared<DoorStage1ToStage2>(m_playerRef, m_cameraRef, spawnPos); };
	m_factoryMap[ObjectKind::kDoor2]    = [&](const Vector2& spawnPos, const Vector2Int& baseMapPos) {return std::make_shared<DoorStage2ToStage3>(m_playerRef, m_cameraRef, spawnPos); };
	m_factoryMap[ObjectKind::kDoor3]    = [&](const Vector2& spawnPos, const Vector2Int& baseMapPos) {return std::make_shared<DoorGameClear>(m_playerRef, m_cameraRef, spawnPos); };
	m_factoryMap[ObjectKind::kDoor4]    = [&](const Vector2& spawnPos, const Vector2Int& baseMapPos) {return std::make_shared<DoorGameClear>(m_playerRef, m_cameraRef, spawnPos); };
	//m_factoryMap[ObjectKind::kDoor5]    = [&](const Vector2& spawnPos, const Vector2Int& baseMapPos) {return std::make_shared<Door>    (m_playerRef, m_cameraRef, spawnPos); };
	//m_factoryMap[ObjectKind::kDoor6]    = [&](const Vector2& spawnPos, const Vector2Int& baseMapPos) {return std::make_shared<Door>    (m_playerRef, m_cameraRef, spawnPos); };
	//m_factoryMap[ObjectKind::kDoor7]    = [&](const Vector2& spawnPos, const Vector2Int& baseMapPos) {return std::make_shared<Door>    (m_playerRef, m_cameraRef, spawnPos); };
	//m_factoryMap[ObjectKind::kDoor8]    = [&](const Vector2& spawnPos, const Vector2Int& baseMapPos) {return std::make_shared<Door>    (m_playerRef, m_cameraRef, spawnPos); };
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

	AvoidOverlappingEnemies();

	for (auto& status : m_isObjectsExist)
	{
		// タイマー加算
		status.IncreaseFrame();
	}
}

void ObjectsController::DrawBehindMapObject() const
{
	for (auto& object : m_objects)
	{
		// これはオブジェクト側にboolを返す関数を作ったほうがいい
		if (object->DrawPriority() == DrawPriority::kFront) continue;

		object->Draw();
	}
}

void ObjectsController::DrawFrontMapObject() const
{
	for (auto& object : m_objects)
	{
		// これはオブジェクト側にboolを返す関数を作ったほうがいい
		if (object->DrawPriority() == DrawPriority::kBehind) continue;

		object->Draw();
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

std::shared_ptr<GameEffect> ObjectsController::SpawnEffect(const std::string& path, const Vector2Int& oneImageSize, const int playSpeed, const Vector2& spawnPos, const Vector2& offset)
{
	m_objects.emplace_back(std::make_shared<GameEffect>(path, oneImageSize, playSpeed, spawnPos, offset));
	return std::dynamic_pointer_cast<GameEffect>(m_objects.back());
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
	spawnSpan(spawnSpanMap.at(ObjectKind::kEmpty)),
	frameDisappear(0),
	isExist(false)
{
}

ObjectAppearanceStatus::ObjectAppearanceStatus(const ObjectKind& spanKind) :
	spawnSpan(spawnSpanMap.at(spanKind)),
	frameDisappear(0),
	isExist(false)
{
}