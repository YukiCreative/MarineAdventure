#pragma once
#include "Scene.h"

// ��ԍŏ��ɕ\�������V�[��
class SceneTitle : public Scene
{
private:
	int m_titleHandle; // ��ŃN���X�����悤��
public:
	SceneTitle();
	~SceneTitle();

	void Update() override;
	void Draw() const override;
};

