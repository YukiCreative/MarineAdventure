#pragma once
#include "Scene.h"
#include <memory>

class Player;
class MapSystem;
class Camera;

// �v���g�^�C�v�J�������ɂ���V�[��
class TestScene : public Scene
{
private:
	int m_frameCount;
	std::shared_ptr<MapSystem> m_map;
	std::shared_ptr<Player> m_player;
	std::shared_ptr<Camera> m_camera;
public:
	TestScene();
	~TestScene();

	virtual void Update() override;
	virtual void Draw() override;
};

