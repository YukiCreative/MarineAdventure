#pragma once
#include "Scene.h"
#include <memory>
#include "Vector2.h"

class ScreenFade;
class ImageObject;
class Camera;
class ButtonSystem;

class SceneGameClear : public Scene
{
private:
	struct Text
	{
		Vector2 pos;
		std::string text;
		int fontHandle;

		Text(const Vector2& initPos, const std::string& setText, const int handle) :
			pos(initPos), text(setText), fontHandle(handle){ }
	};

	std::shared_ptr<Text> m_coinScoreText;
	std::shared_ptr<Text> m_enemyScoreText;
	std::shared_ptr<Text> m_blockScoreText;

	std::shared_ptr<ImageObject> m_back;
	std::shared_ptr<ImageObject> m_clearText;
	std::shared_ptr<ButtonSystem> m_buttonSystem;

	void NormalUpdate() override;

	using State_t = void (SceneGameClear::*)();
	State_t m_state;

	void ChangeState(State_t nextState);

	// ââèoÇä÷êîíPà Ç≈ï™ÇØÇÈ
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

