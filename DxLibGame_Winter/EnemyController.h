#pragma once
#include <memory>
#include <vector>
#include <list>
#include <unordered_map>
#include "Vector2.h"

class Enemy;
class HarmFish;
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
	// Enemy�ɓn������
	Player& m_playerRef;
	Camera& m_cameraRef;

	using EnemyList_t = std::list<std::shared_ptr<Enemy>>;
	EnemyList_t m_enemys;

	// Enemy�̐�����񋓑̂���A�z�ł���悤�Ɋ֐���R�Â���
	using EnemyFactory_t = std::shared_ptr<Enemy>(EnemyController::*)(Vector2 pos);
	std::shared_ptr<Enemy> CreateHarmFish(Vector2 spawnPos);
	std::unordered_map<EnemyKinds, EnemyFactory_t> m_factoryMap;
public:
	EnemyController(Player& player, Camera& camera);

	void Update();
	void Draw();

	/// <summary>
	/// ��ނƈʒu���w�肵�Ă����΂�����Ő����������܂�
	/// </summary>
	void SpawnEnemy(EnemyKinds kind, Vector2 spawnPos);
	/// <summary>
	/// �C���X�^���X�n���Ă�������
	/// </summary>
	void SpawnEnemy(std::shared_ptr<Enemy> enemyInstance);
	/// <summary>
	/// �z��ɂ���G���폜����
	/// �Ƃ͂����Ă��A�h���X��m���Ă���͖̂{�l����������
	/// </summary>
	/// <param name="deleteEnemy">�폜����Enemy�̃X�}�|</param>
	void DespawnEnemy(Enemy* deleteEnemy);
};

