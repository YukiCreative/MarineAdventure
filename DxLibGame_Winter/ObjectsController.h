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
class MapSystem;

struct ObjectAppearanceStatus
{
	bool isExist;
	// �����Ă���̃t���[��
	int frameDisappear;
	// �����Ă��牽�t���[����ɍďo���ł��邩
	int spawnSpan;

	ObjectAppearanceStatus();
	ObjectAppearanceStatus(const ObjectKind& spanKind);

	void IncreaseFrame() { ++frameDisappear; }

	// �f�X�|�[�������Ƃ��Ɏ��s���Ă�
	void Despawn() { frameDisappear = -spawnSpan; }

	bool CanSpawn() const
	{
		// �o�����Ă��Ȃ��āA�����Ă���\���Ɍo�߂���
		return !isExist && frameDisappear > 0;
	}
};

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
	std::weak_ptr<MapSystem> m_mapSystem;

	using ObjectList_t = std::list<std::shared_ptr<GameObject>>;
	ObjectList_t m_objects;

	// �I�u�W�F�N�g�̐�����񋓑̂���A�z�ł���悤�Ɋ֐���R�Â���
	using ObjectFactory_t = std::function<std::shared_ptr<GameObject>(Vector2)>;
	std::unordered_map<ObjectKind, ObjectFactory_t> m_factoryMap;

	// �X�|�[������֘A
	// ���̃}�b�v�ɂ���I�u�W�F�N�g�̏o���󋵂��L��
	std::vector<ObjectAppearanceStatus> m_isObjectsExist;
public:
	ObjectsController(Camera& camera, Player& player, std::weak_ptr<MapSystem> system);

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

	void ResetObjectSpawnStatus();
	bool CanSpawnObject(const Vector2Int& mapPos) const;
	void Despawned(const Vector2Int& mapPos);
};