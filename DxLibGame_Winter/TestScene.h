#pragma once
#include "Scene.h"
#include <memory>

class Player;

// �v���g�^�C�v�J�������ɂ���V�[��
class TestScene : public Scene
{
private:
	int m_frameCount;
	std::shared_ptr<Player> m_player;
public:
	TestScene();
	~TestScene();

	virtual void Update() override;
	virtual void Draw() override;
};

