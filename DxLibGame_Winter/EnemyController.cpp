#include "EnemyController.h"
#include "Enemy.h"

EnemyController::EnemyController(Player& player, Camera& camera) :
	m_cameraRef(camera),
	m_playerRef(player)
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

void EnemyController::SpawnEnemy(std::shared_ptr<Enemy> enemy)
{
	m_enemys.push_back(enemy);
}
