#pragma once
#include <list>
#include <string>
#include <memory>

class ScreenFade;

class Scene
{
private:
	using UpdateState_t = void (Scene::*)();
	UpdateState_t m_update;
	// �t�F�[�h�������ƁA�J�ڂ��鎟�̃V�[��
	// ���܂� �X�R�[�v�̊֌W�チ���o�ϐ��ɂȂ���
	std::string m_fadedNextScene;

	void SceneChangeUpdate();
	void SceneStackUpdate();
	void SceneRemoveUpdate();
protected:
	// 12/25 �t�F�[�h���`����
	ScreenFade& m_fade;
	/// <summary>
	/// �X�V����
	/// </summary>
	virtual void NormalUpdate() = 0;
	// �t�F�[�h�A�E�g���ăV�[���J��
	void SceneChangeWithFadeOut(const std::string& nextSceneId, const int& toralFrame = 60, const float& percent = 100.0f);
	void SceneStackWithFadeOut(const std::string& nextSceneId, const int& toralFrame = 60, const float& percent = 100.0f);
	void SceneRemoveWithFadeOut(const int& toralFrame = 60, const float& percent = 100.0f);
public:
	Scene();
	/// <summary>
	/// �����I�Ƀf�X�g���N�^��virtual�ɂ��Ȃ��Ƃ����Ȃ��ƕ�����
	/// </summary>
	virtual ~Scene() {}
	// SceneController���񂷊֐�
	// �����̏�Ԃ�Normal��Fade������
	void Update();
	/// <summary>
	/// �`��
	/// </summary>
	virtual void Draw() const = 0;
};