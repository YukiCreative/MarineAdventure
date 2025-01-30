#pragma once
#include "Scene.h"
#include <memory>

class ImageObject;
class Camera;
class ButtonSystem;
class ButtonContinue;
class ButtonReturnToTitleFromGameover;
class ButtonQuitGameFromGameover;

class SceneGameover : public Scene
{
private:
	int m_stateFrameCount;

	std::shared_ptr<ImageObject>  m_backGround;
	std::shared_ptr<ButtonSystem> m_buttonController;
	std::shared_ptr<ImageObject>  m_playerDeadSprite;
	std::shared_ptr<ImageObject>  m_gameoverText;

	// �����o�ɂ��ăX�R�[�v���L����
	std::shared_ptr<ButtonContinue> m_buttonContinue;
	std::shared_ptr<ButtonReturnToTitleFromGameover> m_buttonReturnToTitle;
	std::shared_ptr<ButtonQuitGameFromGameover> m_buttonQuitGame;

	void ButtonSetting();

	using GameoverState_t = void (SceneGameover::*)();
	GameoverState_t m_state;
	void PlayerFadeIn();
	void TextFall();
	void ButtonAppear();
	// ���펞
	void NormalState();
public:
	SceneGameover();

	void Init() override;

	void Entry() override;
	void NormalUpdate() override;
	void Draw() const override;

	// �|�[�Y�ɂ������֐�����̂��Ȃ�
	void ReturnToTitle();
	// Continue�Ƃǂ�������������
	void ReturnToGame();
};