#pragma once
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

	Scene& m_scene;
public:
	//static GetInstance();

	void Update();
	void Draw();

	void ChangeScene(Scene& changeScene);
};