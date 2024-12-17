#pragma once
#include <memory>

// �v���g�^�C�v�錾
class Scene;

/// <summary>
/// �V�[����t���ւ��Ď��s����N���X
/// �V���O���g���N���X
/// </summary>
class SceneController
{
private:
	SceneController();
	SceneController(const SceneController&) = delete;
	void operator=(const SceneController&) = delete;

	std::shared_ptr<Scene> m_scene;
	bool m_changedSceneInThisFrame;
public:
	static SceneController& GetInstance();

	void Update();
	void Draw();

	void ChangeScene(std::shared_ptr<Scene> changeScene);
};