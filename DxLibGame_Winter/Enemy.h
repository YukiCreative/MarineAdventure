#pragma once
#include "GameObject.h"

class Camera;

/// <summary>
/// �G�̊��N���X
/// </summary>
class Enemy : public GameObject
{
private:
	Camera& m_camera;
	int m_hp;
protected:
	Enemy(Camera& camera) :
		m_camera(camera),
		m_hp(0)
	{
	}

	// �H�炤
	virtual void Damage() = 0;
	// ����
	virtual void Death() = 0;
};

