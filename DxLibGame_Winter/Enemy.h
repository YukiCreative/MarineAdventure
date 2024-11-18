#pragma once
#include "GameObject.h"

class Camera;

/// <summary>
/// �G�̊��N���X
/// </summary>
class Enemy : public GameObject
{
private:
	// �ق�Ƃ�GameObject�Ɏ�������������
	// Camera��GameObject�Ɋ܂܂��̂Œf�O
	Camera& m_camera;
protected:
	Enemy(Camera& camera) : m_camera(camera) {}

	// �H�炤
	virtual void Damage() = 0;
	// ����
	virtual void Death() = 0;
	// ���̂ǂ���������֐�
	virtual void Attack() = 0;
public:
	// �����̊֐�����GameObject�Ɉڂ����ق�����������
	virtual void Update() = 0;
	virtual void Draw() = 0;
};

