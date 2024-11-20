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
	// map�̐ݒ�
	m_factoryMap[EnemyKinds::kHarmFish] = &EnemyController::CreateHarmFish;
}

void EnemyController::Update()
{
	// ���X�g�̗v�f�S��Update
	for (int i = 0; i < m_enemys.size(); ++i)
	{
		// �����A�u�i�C
		// for�����ŗv�f����������ǂ��Ȃ����
		// �͈�for�����ƃo�O�邪�A���ʂɂ��ƃo�O��Ȃ��@�Ȃ�ŁH
		printf("%d�v�f��", i);
		m_enemys[i]->Update();
	}
	// ��񊮑S�ɏ������I��点����Ŏ��񂾓z�͏���
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
