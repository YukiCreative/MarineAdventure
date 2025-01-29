#include "ColliderTestScene.h"
#include "Scene.h"
#include "SceneController.h"
#include "SceneGame.h"
#include "SceneGameClear.h"
#include "SceneGameover.h"
#include "ScenePause.h"
#include "SceneTitle.h"
#include <cassert>
#include <memory>

SceneController::SceneController() :
	m_hitStopCount(0)
{
	m_factoryMap["Title"]    = [](){return static_cast<std::shared_ptr<Scene>>(std::make_shared<SceneTitle>       ());};
	m_factoryMap["Game"]     = [](){return static_cast<std::shared_ptr<Scene>>(std::make_shared<SceneGame>        ());};
	m_factoryMap["Gameover"] = [](){return static_cast<std::shared_ptr<Scene>>(std::make_shared<SceneGameover>    ());};
	m_factoryMap["ColTest"]  = [](){return static_cast<std::shared_ptr<Scene>>(std::make_shared<ColliderTestScene>());};
	m_factoryMap["Pause"]    = [](){return static_cast<std::shared_ptr<Scene>>(std::make_shared<ScenePause>       ());};
	m_factoryMap["Clear"]    = [](){return static_cast<std::shared_ptr<Scene>>(std::make_shared<SceneGameClear>   ());};

	StackScene("Title");
}

SceneController& SceneController::GetInstance()
{
	static SceneController instance;
	return instance;
}

// Scene�̊֐������̂܂܎��s
void SceneController::Update()
{
	--m_hitStopCount;

	// �q�b�g�X�g�b�v���������Ă��Ȃ����
	if (m_hitStopCount > 0) return;

	// ��ԏ�̃V�[���������s
	m_scenes.back()->Update();
}

void SceneController::Draw()
{
	for (const auto& scene : m_scenes)
	{
		// �`��͑S���ɑ΂��čs��
		scene->Draw();
	}
}

void SceneController::ChangeScene(std::string sceneId)
{
	m_scenes.back()->Leave();
	// �֐������s
	m_scenes.back() = m_factoryMap.at(sceneId)();
	m_scenes.back()->Entry();

#if _DEBUG
	printf("���݂̃V�[�����F%d\n", static_cast<int>(m_scenes.size()));
#endif
}

void SceneController::ResumeScene(std::string sceneId)
{
	m_scenes.back()->Leave();
	// �V�[������񃊃Z�b�g
	m_scenes.clear();
	StackScene(sceneId);

#if _DEBUG
	printf("���݂̃V�[�����F%d\n", static_cast<int>(m_scenes.size()));
#endif
}

void SceneController::StackScene(std::string addSceneId)
{
	// �����悹��̂��ŏ��̃V�[���Ȃ�Leave�����s����Ώۂ��Ȃ����
	if (m_scenes.size()) m_scenes.back()->Leave();

	m_scenes.push_back(m_factoryMap.at(addSceneId)());
	m_scenes.back()->Entry();

#if _DEBUG
	printf("���݂̃V�[�����F%d\n", static_cast<int>(m_scenes.size()));
#endif
}

void SceneController::RemoveSceme()
{
	assert(m_scenes.size() > 1 && "�V�[���������Ȃ��ł�����");

	m_scenes.back()->Leave();
	m_scenes.pop_back();
	// �߂������ɂ�肽�����Ƃ����֐��𑖂点��
	m_scenes.back()->Entry();

#if _DEBUG
	printf("���݂̃V�[�����F%d\n", static_cast<int>(m_scenes.size()));
#endif
}

void SceneController::HitStop(const int frame)
{
	m_hitStopCount = frame;
}