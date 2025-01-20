#include "ObjectsController.h"
#include "Enemy.h"
#include <vector>
#include <cassert>
#include "HarmFish.h"
#include "Player.h"
#include "Camera.h"
#include "ObjectKind.h"
#include "Boss.h"
#include "Door.h"
#include "MapSystem.h"

ObjectsController::ObjectsController(Camera& camera, Player& player) :
	m_playerRef(player),
	m_cameraRef(camera)
{
	// map�̐ݒ�
	// function���Ă����[
	m_factoryMap[ObjectKind::kHarmFish] = [&](Vector2 spawnPos) {return std::make_shared<HarmFish>(m_playerRef, m_cameraRef, spawnPos); };
	m_factoryMap[ObjectKind::kBoss]     = [&](Vector2 spawnPos) {return std::make_shared<Boss>    (m_playerRef, m_cameraRef, spawnPos); };
	m_factoryMap[ObjectKind::kDoor1]    = [&](Vector2 spawnPos) {return std::make_shared<Door>    (m_playerRef, m_cameraRef, spawnPos, static_cast<int>(ObjectKind::kDoor1)); };
	m_factoryMap[ObjectKind::kDoor2]    = [&](Vector2 spawnPos) {return std::make_shared<Door>    (m_playerRef, m_cameraRef, spawnPos, static_cast<int>(ObjectKind::kDoor2)); };
	m_factoryMap[ObjectKind::kDoor3]    = [&](Vector2 spawnPos) {return std::make_shared<Door>    (m_playerRef, m_cameraRef, spawnPos, static_cast<int>(ObjectKind::kDoor3)); };
	m_factoryMap[ObjectKind::kDoor4]    = [&](Vector2 spawnPos) {return std::make_shared<Door>    (m_playerRef, m_cameraRef, spawnPos, static_cast<int>(ObjectKind::kDoor4)); };
	m_factoryMap[ObjectKind::kDoor5]    = [&](Vector2 spawnPos) {return std::make_shared<Door>    (m_playerRef, m_cameraRef, spawnPos, static_cast<int>(ObjectKind::kDoor5)); };
	m_factoryMap[ObjectKind::kDoor6]    = [&](Vector2 spawnPos) {return std::make_shared<Door>    (m_playerRef, m_cameraRef, spawnPos, static_cast<int>(ObjectKind::kDoor6)); };
	m_factoryMap[ObjectKind::kDoor7]    = [&](Vector2 spawnPos) {return std::make_shared<Door>    (m_playerRef, m_cameraRef, spawnPos, static_cast<int>(ObjectKind::kDoor7)); };
	m_factoryMap[ObjectKind::kDoor8]    = [&](Vector2 spawnPos) {return std::make_shared<Door>    (m_playerRef, m_cameraRef, spawnPos, static_cast<int>(ObjectKind::kDoor8)); };
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
		// ���̓G���܂������Ă��烊�X�g�ɓ���Ƃ�
		if (!object->IsDeleted())
		{
			// �|�C���^���R�s�[
			aliveObjects.push_back(object);
		}
	}
	// �͂ݏo���v�f�͎����I�ɍ폜�����
	m_objects = aliveObjects;
}

void ObjectsController::Draw()
{
	for (auto& enemy : m_objects)
	{
		enemy->Draw();
	}
}

void ObjectsController::SpawnObject(ObjectKind kind, Vector2 spawnPos)
{
	if (kind == ObjectKind::kEmpty) return;
	m_objects.push_back(m_factoryMap[kind](spawnPos));
}

void ObjectsController::SpawnObject(std::shared_ptr<GameObject> objectInstance)
{
	m_objects.push_back(objectInstance);
}

void ObjectsController::ClearObjects()
{
	m_objects.clear();
}