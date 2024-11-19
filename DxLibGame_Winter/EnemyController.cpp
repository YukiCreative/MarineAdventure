#include "EnemyController.h"
#include "Enemy.h"
#include <vector>
#include <cassert>

EnemyController::EnemyController()
{
	
}

void EnemyController::Update()
{
	// リストの要素全部Update
	for (auto& enemy : m_enemys)
	{
		enemy->Update();
	}
}

void EnemyController::Draw()
{
	for (auto& enemy : m_enemys)
	{
		enemy->Draw();
	}
}

void EnemyController::SpawnEnemy(EnemyKinds kind)
{
	m_enemys.push_back(enemy);
}

void EnemyController::DespawnEnemy(Enemy& deleteEnemy)
{
	auto it = m_enemys.begin();
	for (auto& enemy : m_enemys)
	{
		// きたないけどゆるして
		if (enemy.get() == &deleteEnemy)
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
