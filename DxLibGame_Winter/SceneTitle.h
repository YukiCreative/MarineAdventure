#pragma once
#include "Scene.h"

// 一番最初に表示されるシーン
class SceneTitle : public Scene
{
private:
	int m_titleHandle; // 後でクラス化しようね
public:
	SceneTitle();
	~SceneTitle();

	void Update() override;
	void Draw() const override;
};

