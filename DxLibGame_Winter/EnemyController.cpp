#include "EnemyController.h"
#include "Enemy.h"
#include <vector>
#include <cassert>

void EnemyController::Update()
{
	// ���X�g�̗v�f�S��Update
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

void EnemyController::SpawnEnemy(std::shared_ptr<Enemy> enemy)
{
	m_enemys.push_back(enemy);
}

void EnemyController::DespawnEnemy(Enemy& deleteEnemy)
{
	auto it = m_enemys.begin();
	for (auto& enemy : m_enemys)
	{
		// �����Ȃ����ǂ�邵��
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
	assert(false && "����ȗv�f�͂���܂���");
}
