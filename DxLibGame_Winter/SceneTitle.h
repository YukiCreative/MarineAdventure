#pragma once
#include "Scene.h"
#include <memory>

class ImageObject;
class Camera;
class ScreenFade;
class ButtonSystem;
class Animation;

// ˆê”ÔÅ‰‚É•\¦‚³‚ê‚éƒV[ƒ“
class SceneTitle : public Scene
{
private:
	std::shared_ptr<ImageObject>  m_backGround;
	std::shared_ptr<ButtonSystem> m_buttonSystem;
	std::shared_ptr<ImageObject>  m_titleLogo;
	std::shared_ptr<Animation>    m_nowAnim;
	std::shared_ptr<Animation>    m_playerIdleAnim;
	std::shared_ptr<Animation>    m_playerAttackAnim;

	void ButtonInit();

	// NormalUpdate‚Ì’†‚É‚³‚ç‚Éó‘Ô‚ğ
	using State_t = void (SceneTitle::*)();
	State_t m_state;
	void Normal();
	void StartAnim();
public:
	void Init() override;

	void Entry() override;
	void NormalUpdate() override;
	void Draw() const override;

	void GameStart();
};

