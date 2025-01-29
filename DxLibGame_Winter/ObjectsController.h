#pragma once
#include "ObjectKind.h"
#include "Vector2.h"
#include <functional>
#include <list>
#include <memory>
#include <unordered_map>
#include <vector>

class HarmFish;
class Player;
class Camera;
class GameObject;
class MapSystem;
class GameEffect;
class Enemy;

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

	void Spawn()
	{
		isExist = true;
	}

	// �f�X�|�[�������Ƃ��Ɏ��s���Ă�
	void Despawn() 
	{
		frameDisappear = -spawnSpan;
		isExist = false;
	}

	bool CanSpawn() const
	{
		// �o�����Ă��Ȃ��āA�����Ă���\���Ɍo�߂���
		return !isExist && frameDisappear >= 0;
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

	using ObjectList_t = std::list<std::shared_ptr<GameObject>>;
	ObjectList_t m_objects;

	// �I�u�W�F�N�g�̐�����񋓑̂���A�z�ł���悤�Ɋ֐���R�Â���
	using ObjectFactory_t = std::function<std::shared_ptr<GameObject>(const Vector2& spawnPos, const Vector2Int& baseMapPos)>;
	std::unordered_map<ObjectKind, ObjectFactory_t> m_factoryMap;

	// �X�|�[������֘A
	// ���̃}�b�v�ɂ���I�u�W�F�N�g�̏o���󋵂��L��
	std::vector<ObjectAppearanceStatus> m_isObjectsExist;
	Vector2Int m_mapSize;

	void AvoidOverlappingEnemies();
public:
	ObjectsController(Camera& camera, Player& player);

	void Update();
	void DrawFrontMapObject() const;
	void DrawBehindMapObject() const;

	/// <summary>
	/// ��ނƈʒu���w�肵�Ă����΂�����Ő����������܂�
	/// </summary>
	void SpawnObject(const ObjectKind& kind, const Vector2& spawnPos, const Vector2Int& baseMapPos);
	/// <summary>
	/// �C���X�^���X�n���Ă�������
	/// </summary>
	void SpawnObject(std::shared_ptr<GameObject> objectInstance);
	
	void ClearObjects();

	// ���̃N���X����A�N�Z�X�������AMapSytem�̃����o���g�������Ƃ�����
	void ResetObjectSpawnStatus(MapSystem& system);
	bool CanSpawnObject(const Vector2Int& mapPos) const;
	void Despawned(const Vector2Int& mapPos);
};