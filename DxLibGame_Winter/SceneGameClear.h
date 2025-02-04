#pragma once
#include "Scene.h"
#include <memory>
#include "Vector2.h"

class ScreenFade;
class ImageObject;
class Camera;
class ButtonSystem;
class ButtonReturnToTitleFromClearScene;

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
	// 描画する値
	float m_lerpCoinScore;
	std::shared_ptr<Text> m_enemyScoreText;
	float m_lerpEnemyScore;
	std::shared_ptr<Text> m_blockScoreText;
	float m_lerpBlockScore;
	std::shared_ptr<Text> m_timeScoreText;
	float m_lerpTimeScore;
	std::shared_ptr<Text> m_totalScoreText;
	float m_lerpTotalScore;
	// 結局フォントハンドルがメンバに　悲しい
	int m_font;

	std::shared_ptr<ImageObject> m_back;
	std::shared_ptr<ImageObject> m_clearText;
	std::shared_ptr<ButtonSystem> m_buttonSystem;
	std::shared_ptr<ButtonReturnToTitleFromClearScene> m_button;

	void NormalUpdate() override;

	using State_t = void (SceneGameClear::*)();
	State_t m_state;
	int m_stateFrameCount;

	void ChangeState(State_t nextState);

	// 演出を関数単位で分ける
	void AppearGameClearText();
	void AppearGetCoinNum();
	void AppearKillEnemyNum();
	void AppearBreakBlockNum();
	void AppearTimeBonusNum();
	void AppearScoreNum();
	void AppearButton();
	// NormalUpdateと間違えやすいな
	void NormalState();
public:
	~SceneGameClear();

	void Init() override;

	void Draw() const override;

	void Entry() override;

	void ReturnToTitle();
};

