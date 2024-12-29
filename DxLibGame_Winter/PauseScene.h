#pragma once
#include "Scene.h"
#include <memory>

class BackGround;
class Camera;
class ButtonSystem;

// ���̃N���X�ɂ�����������
// �I�v�V�����V�[����
// �^�C�g���ɖ߂�
// �����p�̉摜
class PauseScene : public Scene
{
private:
	std::shared_ptr<Camera> m_camera;
	std::shared_ptr<BackGround> m_back;
	std::shared_ptr<ButtonSystem> m_buttonSystem;
public:
	PauseScene();

	void NormalUpdate() override;
	void Draw() const override;

	void ReturnToTitle();
	void RetrunToGame();
};

