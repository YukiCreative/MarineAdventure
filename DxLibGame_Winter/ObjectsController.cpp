#include "ObjectsController.h"
#include "Enemy.h"
#include <vector>
#include <cassert>
#include "HarmFish.h"
#include "Player.h"
#include "Camera.h"
#include "ObjectKind.h"

std::shared_ptr<GameObject> ObjectsController::CreateHarmFish(Vector2 spawnPos)
{
	return std::static_pointer_cast<Enemy>(std::make_shared<HarmFish>(m_playerRef, m_cameraRef, spawnPos));
}

ObjectsController::ObjectsController(Player& player, Camera& camera) :
	m_playerRef(player),
	m_cameraRef(camera)
{
	// mapの設定
	m_factoryMap[ObjectKind::kHarmFish] = &ObjectsController::CreateHarmFish;
}

void ObjectsController::Update()
{
	// 死亡者リストを宣言
	std::vector<std::shared_ptr<GameObject>> deathNote;
	// リストの要素全部Update
	for (auto& object : m_objects)
	{
		object->Update();
		// この敵が死んだら死亡者リストに入れとく
		if (object->IsDead())
		{
			// ポインタをコピー
			deathNote.push_back(object);
		}
	}

	// すべての処理が終わった後に、消える予定の敵を削除する
	for (const auto& deathObject : deathNote)
	{
		// 絶対遅いけど仕様追加するのが大事よな
		auto iterator = std::remove(m_objects.begin(), m_objects.end(), deathObject);
		// このイテレータはちょうどremoveした要素を指している
		m_objects.erase(iterator);
	}
	// ここでEnemyのスマポは参照を失うので消える。はず。
	deathNote.clear();
}

void ObjectsController::Draw()
{
	for (auto& enemy : m_objects)
	{
		enemy->Draw();
	}
}

void ObjectsController::SpawnObject(ObjectKind kind, Vector2 spawnPos)
{
	if (kind == ObjectKind::kEmpty) return;
	m_objects.push_back((this->*m_factoryMap[kind])(spawnPos));
}

void ObjectsController::SpawnObject(std::shared_ptr<GameObject> objectInstance)
{
	m_objects.push_back(objectInstance);
}