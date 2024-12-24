#pragma once
#include <memory>
#include <list>

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

	using SceneList_t = std::list<std::shared_ptr<Scene>>;
	SceneList_t m_scenes;
	bool m_changedSceneInThisFrame;
public:
	static SceneController& GetInstance();

	// ��ԏ�̃V�[���̂ݎ��s�����
	void Update();
	void Draw();

	// �����s���̃V�[����ʂ̂��̂ɑւ���
	void ChangeScene(std::shared_ptr<Scene> changeScene);
	// �V�[�����d�˂�
	void StackScene(std::shared_ptr<Scene> addScene);
	// �Ō���̃V�[�����폜
	void RemoveSceme();
};