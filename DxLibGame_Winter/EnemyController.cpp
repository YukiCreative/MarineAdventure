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
	// ���S�҃��X�g��錾
	std::vector<std::shared_ptr<Enemy>> deathNote;
	// ���X�g�̗v�f�S��Update
	for (auto& enemy : m_enemys)
	{
		enemy->Update();
		// ���̓G�����񂾂玀�S�҃��X�g�ɓ���Ƃ�
		if (enemy->IsDead())
		{
			deathNote.push_back(enemy);
		}
	}
	
	// vector�Ȃ炱��ňꔭ
	//for (int i = 0; i < m_enemys.size(); i++)
	//{
	//	m_enemys[i]->Update();
	//	if (m_enemys[i]->IsDead())
	//	{
	//		deathNote.push_back(m_enemys[i]);
	//		m_enemys.erase(m_enemys.begin() + i);
	//	}
	//}
	//m_enemys.shrink_to_fit();

	// ���ׂĂ̏������I�������ɁA������\��̓G���폜����
	for (const auto& deathEnemy : deathNote)
	{
		// ��Βx�����ǎd�l�ǉ�����̂��厖���
		auto iterator = std::remove(m_enemys.begin(), m_enemys.end(), deathEnemy);
		// ���̃C�e���[�^�͂��傤��remove�����v�f���w���Ă����̂ł������c
		m_enemys.erase(iterator);
	}
	// ������Enemy�̃X�}�|�͎Q�Ƃ������̂ŏ�����B�͂��B
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
		// �����Ȃ����ǂ�邵��
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
	assert(false && "����ȗv�f�͂���܂���");
}
