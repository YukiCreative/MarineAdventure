#pragma once
#include <memory>
#include <list>

class Enemy;
class Player;
class Camera;

/// <summary>
/// �V�[���ł�����C���X�^���X������
/// Enemy���Ǘ����Ă��炤
/// </summary>
class EnemyController
{
private:
	using EnemyList_t = std::list<std::shared_ptr<Enemy>>;
	EnemyList_t m_enemys;
	Player& m_playerRef;
	Camera& m_cameraRef;
public:
	EnemyController(Player& player, Camera& camera);

	void Update();
	void Draw();

	/// <summary>
	/// list�Ɉ����œn���ꂽ�G��ǉ����܂��B
	/// mapchip�Ƃ��ɌĂ�ł��炤�C���[�W
	/// </summary>
	/// <param name="enemy">�G</param>
	void SpawnEnemy(std::shared_ptr<Enemy> enemy);
};

