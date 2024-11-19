#pragma once
#include <memory>
#include <vector>
#include <unordered_map>

class Enemy;
class Player;
class Camera;

enum class EnemyKinds
{
	kHarmFish,
};

/// <summary>
/// �V�[���ł�����C���X�^���X������
/// Enemy���Ǘ����Ă��炤
/// </summary>
class EnemyController
{
private:
	using EnemyList_t = std::vector<std::shared_ptr<Enemy>>;
	EnemyList_t m_enemys;
	std::unordered_map<EnemyKinds, >
public:
	EnemyController();

	void Update();
	void Draw();

	/// <summary>
	/// list�Ɉ����œn���ꂽ�G��ǉ����܂��B
	/// mapchip�Ƃ��ɌĂ�ł��炤�C���[�W
	/// </summary>
	/// <param name="enemy">�G</param>
	void SpawnEnemy(EnemyKinds kind);
	/// <summary>
	/// �z��ɂ���G���폜����
	/// �Ƃ͂����Ă��A�h���X��m���Ă���͖̂{�l����������
	/// </summary>
	/// <param name="deleteEnemy">�폜����Enemy�̃X�}�|</param>
	void DespawnEnemy(Enemy& deleteEnemy);
};

