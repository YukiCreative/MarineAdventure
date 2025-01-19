#pragma once
#include <memory>
#include <vector>
#include <list>
#include <unordered_map>
#include "Vector2.h"
#include "ObjectKind.h"
#include <functional>

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

	// �I�u�W�F�N�g�̐�����񋓑̂���A�z�ł���悤�Ɋ֐���R�Â���
	using ObjectFactory_t = std::function<std::shared_ptr<GameObject>(Vector2)>;
	std::unordered_map<ObjectKind, ObjectFactory_t> m_factoryMap;
public:
	ObjectsController(Camera& camera, Player& player);

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
	
	void ClearObjects();
};