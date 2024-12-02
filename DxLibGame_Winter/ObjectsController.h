#pragma once
#include <memory>
#include <vector>
#include <list>
#include <unordered_map>
#include "Vector2.h"
#include "ObjectKind.h"

class HarmFish;
class Player;
class Camera;
class GameObject;

/// <summary>
/// �V�[���ł�����C���X�^���X������
/// �Ǘ����Ă��炤
/// </summary>
class ObjectsController
{
private:
	// Enemy�ɓn������
	Player& m_playerRef;
	Camera& m_cameraRef;

	using ObjectList_t = std::list<std::shared_ptr<GameObject>>;
	ObjectList_t m_objects;

	// Enemy�̐�����񋓑̂���A�z�ł���悤�Ɋ֐���R�Â���
	using ObjectFactory_t = std::shared_ptr<GameObject>(ObjectsController::*)(Vector2 pos);
	std::shared_ptr<GameObject> CreateHarmFish(Vector2 spawnPos);
	std::unordered_map<ObjectKind, ObjectFactory_t> m_factoryMap;
public:
	ObjectsController(Player& player, Camera& camera);

	void Update();
	void Draw();

	/// <summary>
	/// ��ނƈʒu���w�肵�Ă����΂�����Ő����������܂�
	/// </summary>
	void SpawnObject(ObjectKind kind, Vector2 spawnPos);
	/// <summary>
	/// �C���X�^���X�n���Ă�������
	/// </summary>
	void SpawnObject(std::shared_ptr<GameObject> objectInstance);
	/// <summary>
	/// �z��ɂ���G���폜����
	/// �Ƃ͂����Ă��A�h���X��m���Ă���͖̂{�l����������
	/// </summary>
	/// <param name="deleteEnemy">�폜����Enemy�̃X�}�|</param>
	void DespawnEnemy(GameObject* deleteEnemy);
};