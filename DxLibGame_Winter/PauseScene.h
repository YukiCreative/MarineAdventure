#pragma once
#include "Scene.h"
#include <memory>

class BackGround;
class ScreenFade;
class Camera;

// ���̃N���X�ɂ�����������
// �I�v�V�����V�[����
// �^�C�g���ɖ߂�
// �����p�̉摜
class PauseScene : public Scene
{
private:
	std::shared_ptr<Camera> m_camera;
	ScreenFade& m_fade;
	std::shared_ptr<BackGround> m_back;
public:
	PauseScene();

	void NormalUpdate() override;
	void Draw() const override;
};

