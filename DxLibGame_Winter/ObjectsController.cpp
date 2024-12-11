#include "ObjectsController.h"
#include "Enemy.h"
#include <vector>
#include <cassert>
#include "HarmFish.h"
#include "Player.h"
#include "Camera.h"
#include "ObjectKind.h"

std::shared_ptr<GameObject> ObjectsController::CreateHarmFish(Vector2 spawnPos)
{
	return std::static_pointer_cast<Enemy>(std::make_shared<HarmFish>(m_playerRef, m_cameraRef, spawnPos));
}

ObjectsController::ObjectsController(Player& player, Camera& camera) :
	m_playerRef(player),
	m_cameraRef(camera)
{
	// map�̐ݒ�
	m_factoryMap[ObjectKind::kHarmFish] = &ObjectsController::CreateHarmFish;
}

void ObjectsController::Update()
{
	// ���S�҃��X�g��錾
	std::vector<std::shared_ptr<GameObject>> deathNote;
	// ���X�g�̗v�f�S��Update
	for (auto& object : m_objects)
	{
		object->Update();
		// ���̓G�����񂾂玀�S�҃��X�g�ɓ���Ƃ�
		if (object->IsDead())
		{
			// �|�C���^���R�s�[
			deathNote.push_back(object);
		}
	}

	// ���ׂĂ̏������I�������ɁA������\��̓G���폜����
	for (const auto& deathObject : deathNote)
	{
		// ��Βx�����ǎd�l�ǉ�����̂��厖���
		auto iterator = std::remove(m_objects.begin(), m_objects.end(), deathObject);
		// ���̃C�e���[�^�͂��傤��remove�����v�f���w���Ă���
		m_objects.erase(iterator);
	}
	// ������Enemy�̃X�}�|�͎Q�Ƃ������̂ŏ�����B�͂��B
	deathNote.clear();
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
	m_objects.push_back((this->*m_factoryMap[kind])(spawnPos));
}

void ObjectsController::SpawnObject(std::shared_ptr<GameObject> objectInstance)
{
	m_objects.push_back(objectInstance);
}