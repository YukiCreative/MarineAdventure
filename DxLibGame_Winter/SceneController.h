#pragma once
#include <memory>
#include <list>
#include <unordered_map>
#include <string>

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

	using SceneFactory_t = std::shared_ptr<Scene> (*)();
	std::unordered_map<std::string, SceneFactory_t> m_factoryMap;

	int m_hitStopCount;
public:
	static SceneController& GetInstance();

	// ��ԏ�̃V�[���̂ݎ��s�����
	void Update();
	void Draw();

	// �����s���̃V�[����ʂ̂��̂ɑւ���
	void ChangeScene(std::string sceneId);
	// ���W�J���Ă���V�[����S���ЂÂ��ĐV�����V�[��������ɂ���
	void ResumeScene(std::string sceneId);
	// �V�[�����d�˂�
	void StackScene(std::string addSceneId);
	// �Ō���̃V�[�����폜
	void RemoveSceme();

	// �����s���̃V�[����Ԃ�
	std::shared_ptr<Scene> CurrentScene() { return m_scenes.back(); }
	void HitStop(const int frame);
};