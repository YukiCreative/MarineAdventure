#pragma once
#include "GameObject.h"

/// <summary>
/// �w�i�摜��\��������
/// ���i�Ȃ̂Ŏ�O(�}�b�v�`�b�v�A�v���C���[)��������蓮��������
/// </summary>
class BackGround : public GameObject
{
private:
	int m_graphHandle;
public:
	BackGround();

	void Update() override;
	void Draw() const override;
};

