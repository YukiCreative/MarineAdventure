#include "Boss.h"
#include "Camera.h"
#include "DestructibleBlock.h"
#include "Door.h"
#include "Enemy.h"
#include "GameEffect.h"
#include "HarmFish.h"
#include "MapSystem.h"
#include "ObjectKind.h"
#include "ObjectsController.h"
#include "Player.h"
#include <cassert>
#include <vector>

namespace
{
	// ����탁���o�ϐ��ɂ����ق����悳�������Ȃ� ���Ȃ�����
	std::unordered_map<ObjectKind, int> spawnSpanMap =
	{
		// �ďo���̃N�[���^�C��������̂́A��������o�����āA�������
		{ObjectKind::kEmpty, 0},
		{ObjectKind::kHarmFish, Game::kFrameRate * 60},
		{ObjectKind::kBoss,  0},
		{ObjectKind::kDoor1, 0},
		{ObjectKind::kDoor2, 0},
		{ObjectKind::kDoor3, 0},
		{ObjectKind::kDoor4, 0},
		{ObjectKind::kDoor5, 0},
		{ObjectKind::kDoor6, 0},
		{ObjectKind::kDoor7, 0},
		{ObjectKind::kDoor8, 0},
	};
}

ObjectsController::ObjectsController(Camera& camera, Player& player) :
	m_playerRef(player),
	m_cameraRef(camera)
{
	// map�̐ݒ�
	// function���Ă����[
	m_factoryMap[ObjectKind::kHarmFish] = [&](const Vector2& spawnPos, const Vector2Int& baseMapPos) {return std::make_shared<HarmFish>(*this, m_playerRef, m_cameraRef, spawnPos, baseMapPos); };
	m_factoryMap[ObjectKind::kBoss]     = [&](const Vector2& spawnPos, const Vector2Int& baseMapPos) {return std::make_shared<Boss>    (*this, m_playerRef, m_cameraRef, spawnPos, baseMapPos); };
	m_factoryMap[ObjectKind::kDestructibleBlock] = [&](const Vector2& spawnPos, const Vector2Int& baseMapPos) {return std::make_shared<DestructibleBlock>(m_cameraRef, spawnPos, m_playerRef); };
	m_factoryMap[ObjectKind::kDoor1]    = [&](const Vector2& spawnPos, const Vector2Int& baseMapPos) {return std::make_shared<Door>    (m_playerRef, m_cameraRef, spawnPos, static_cast<int>(ObjectKind::kDoor1)); };
	m_factoryMap[ObjectKind::kDoor2]    = [&](const Vector2& spawnPos, const Vector2Int& baseMapPos) {return std::make_shared<Door>    (m_playerRef, m_cameraRef, spawnPos, static_cast<int>(ObjectKind::kDoor2)); };
	m_factoryMap[ObjectKind::kDoor3]    = [&](const Vector2& spawnPos, const Vector2Int& baseMapPos) {return std::make_shared<Door>    (m_playerRef, m_cameraRef, spawnPos, static_cast<int>(ObjectKind::kDoor3)); };
	m_factoryMap[ObjectKind::kDoor4]    = [&](const Vector2& spawnPos, const Vector2Int& baseMapPos) {return std::make_shared<Door>    (m_playerRef, m_cameraRef, spawnPos, static_cast<int>(ObjectKind::kDoor4)); };
	m_factoryMap[ObjectKind::kDoor5]    = [&](const Vector2& spawnPos, const Vector2Int& baseMapPos) {return std::make_shared<Door>    (m_playerRef, m_cameraRef, spawnPos, static_cast<int>(ObjectKind::kDoor5)); };
	m_factoryMap[ObjectKind::kDoor6]    = [&](const Vector2& spawnPos, const Vector2Int& baseMapPos) {return std::make_shared<Door>    (m_playerRef, m_cameraRef, spawnPos, static_cast<int>(ObjectKind::kDoor6)); };
	m_factoryMap[ObjectKind::kDoor7]    = [&](const Vector2& spawnPos, const Vector2Int& baseMapPos) {return std::make_shared<Door>    (m_playerRef, m_cameraRef, spawnPos, static_cast<int>(ObjectKind::kDoor7)); };
	m_factoryMap[ObjectKind::kDoor8]    = [&](const Vector2& spawnPos, const Vector2Int& baseMapPos) {return std::make_shared<Door>    (m_playerRef, m_cameraRef, spawnPos, static_cast<int>(ObjectKind::kDoor8)); };
}

void ObjectsController::Update()
{
	// �����҃��X�g��錾
	// ���񂾂̂��������ȒP
	ObjectList_t aliveObjects;
	// ���X�g�̗v�f�S��Update
	for (auto& object : m_objects)
	{
		object->Update();
		// ���̃I�u�W�F�N�g���܂������Ă��烊�X�g�ɓ���Ƃ�
		if (!object->IsDeleted())
		{
			// �|�C���^���R�s�[
			aliveObjects.emplace_back(object);
		}
		else
		{
			Despawned(object->GetBaseMapPos());
		}
	}
	// �͂ݏo���v�f�͎����I�ɍ폜�����
	m_objects = aliveObjects;

	for (auto& status : m_isObjectsExist)
	{
		// �^�C�}�[���Z
		status.IncreaseFrame();
	}
}

void ObjectsController::Draw()
{
	for (auto& enemy : m_objects)
	{
		enemy->Draw();
	}
}

void ObjectsController::SpawnObject(const ObjectKind& kind, const Vector2& spawnPos, const Vector2Int& baseMapPos)
{
	if (kind == ObjectKind::kEmpty) return;
	m_objects.push_back(m_factoryMap[kind](spawnPos, baseMapPos));
	// �o���������Ƃ��L��������
	m_isObjectsExist[baseMapPos.x + baseMapPos.y * m_mapSize.x].Spawn();
}

void ObjectsController::SpawnObject(std::shared_ptr<GameObject> objectInstance)
{
	m_objects.push_back(objectInstance);
}

void ObjectsController::ClearObjects()
{
	m_objects.clear();
}

bool ObjectsController::CanSpawnObject(const Vector2Int& mapPos) const
{
	// ����
	// ���������o�����Ă��Ȃ��āA�������Ă���ďo���\�ȕb���o���Ă�����
	// �����ŁA�}�b�v�͈̔͊O��������false��Ԃ�
	if (mapPos.x < 0 || mapPos.y < 0 || mapPos.x >= m_mapSize.x || mapPos.y >= m_mapSize.y) return false;

	ObjectAppearanceStatus status = m_isObjectsExist[mapPos.x + m_mapSize.x * mapPos.y];
	return status.CanSpawn();
}

void ObjectsController::Despawned(const Vector2Int& mapPos)
{
	m_isObjectsExist[mapPos.x + m_mapSize.x * mapPos.y].Despawn();
}

void ObjectsController::ResetObjectSpawnStatus(MapSystem& system)
{
	m_mapSize = system.GetMapSize();
	// �}�b�v�`�b�v�̐�����������
	m_isObjectsExist.resize(m_mapSize.x * m_mapSize.y);

	// �͈�for�g���Ȃ�����
	for (int i = 0; i < m_isObjectsExist.size(); ++i)
	{
		m_isObjectsExist[i] = ObjectAppearanceStatus(system.GetObjKind(i));
	}
}

// =====================================

ObjectAppearanceStatus::ObjectAppearanceStatus() :
	spawnSpan(spawnSpanMap[ObjectKind::kEmpty]),
	frameDisappear(0),
	isExist(false)
{
}

ObjectAppearanceStatus::ObjectAppearanceStatus(const ObjectKind& spanKind) :
	spawnSpan(spawnSpanMap[spanKind]),
	frameDisappear(0),
	isExist(false)
{
}