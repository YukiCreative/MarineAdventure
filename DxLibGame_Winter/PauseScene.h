#pragma once
#include "Scene.h"

// ���̃N���X�ɂ�����������
// �I�v�V�����V�[����
// �^�C�g���ɖ߂�
// �����p�̉摜
class PauseScene : public Scene
{
private:
public:
	void Update() override;
	void Draw() const override;
};

