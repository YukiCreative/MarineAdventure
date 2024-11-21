#include "EnemyController.h"
#include "Enemy.h"
#include <vector>
#include <cassert>
#include "HarmFish.h"
#include "Player.h"
#include "Camera.h"

std::shared_ptr<Enemy> EnemyController::CreateHarmFish(Vector2 spawnPos)
{
	return std::static_pointer_cast<Enemy>(std::make_shared<HarmFish>(m_playerRef, m_cameraRef, *this, spawnPos));
}

EnemyController::EnemyController(Player& player, Camera& camera) :
	m_playerRef(player),
	m_cameraRef(camera)
{
	// mapの設定
	m_factoryMap[EnemyKinds::kHarmFish] = &EnemyController::CreateHarmFish;
}

void EnemyController::Update()
{
	// 死亡者リストを宣言
	std::vector<std::shared_ptr<Enemy>> deathNote;
	// リストの要素全部Update
	for (auto& enemy : m_enemys)
	{
		enemy->Update();
		// この敵が死んだら死亡者リストに入れとく
		if (enemy->IsDead())
		{
			deathNote.push_back(enemy);
		}
	}
	// すべての処理が終わった後に、消える予定の敵を削除する
	for (const auto& deathEnemy : deathNote)
	{
		auto iterator = std::remove(m_enemys.begin(), m_enemys.end(), deathEnemy);
		m_enemys.erase(--iterator);
	}
	// ここでEnemyのスマポは参照を失うので消える。はず。
	deathNote.clear();
}

void EnemyController::Draw()
{
	for (auto& enemy : m_enemys)
	{
		enemy->Draw();
	}
}

void EnemyController::SpawnEnemy(EnemyKinds kind, Vector2 spawnPos)
{
	m_enemys.push_back((this->*m_factoryMap[kind])(spawnPos));
}

void EnemyController::SpawnEnemy(std::shared_ptr<Enemy> enemyInstance)
{
	m_enemys.push_back(enemyInstance);
}

void EnemyController::DespawnEnemy(Enemy* deleteEnemy)
{
	auto it = m_enemys.begin();
	for (auto& enemy : m_enemys)
	{
		// きたないけどゆるして
		if (enemy.get() == deleteEnemy)
		{
			m_enemys.erase(it);
			return;
		}
		else
		{
			++it;
		}
	}
	assert(false && "そんな要素はありません");
}
