#pragma once
#include "Scene.h"
#include <memory>

class ScreenFade;
class ImageObject;
class Camera;
class ButtonSystem;

class SceneGameClear : public Scene
{
private:
	std::shared_ptr<ImageObject> m_back;
	std::shared_ptr<ImageObject> m_clearText;
	std::shared_ptr<ButtonSystem> m_buttonSystem;

	// 文字書くクラスにしたほうがいいけどしない
	// なぜなら時間がないから
	int m_fontHandle;

	void NormalUpdate() override;

	using State_t = void (SceneGameClear::*)();
	State_t m_state;

	void ChangeState(State_t nextState);

	// 演出を関数単位で分ける
	void AppearGameClearText();
	void AppearGetCoinNum();
	void AppearKillEnemyNum();
	void AppearBreakBlockNum();
	void AppearTimeBonusNum();
	void AppearScoreNum();
	void AppearButton();
public:
	void Init() override;

	void Draw() const override;

	void Entry() override;
};

