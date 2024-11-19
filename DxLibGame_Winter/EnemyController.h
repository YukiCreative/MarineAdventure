#pragma once
#include <memory>
#include <vector>

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
	using EnemyList_t = std::vector<std::shared_ptr<Enemy>>;
	EnemyList_t m_enemys;
public:

	void Update();
	void Draw();

	/// <summary>
	/// list�Ɉ����œn���ꂽ�G��ǉ����܂��B
	/// mapchip�Ƃ��ɌĂ�ł��炤�C���[�W
	/// </summary>
	/// <param name="enemy">�G</param>
	void SpawnEnemy(std::shared_ptr<Enemy> enemy);
	/// <summary>
	/// �z��ɂ���G���폜����
	/// �Ƃ͂����Ă��A�h���X��m���Ă���͖̂{�l����������
	/// </summary>
	/// <param name="deleteEnemy">�폜����Enemy�̃X�}�|</param>
	void DespawnEnemy(Enemy& deleteEnemy);
};

