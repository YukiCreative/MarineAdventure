#pragma once
#include "Button.h"
#include <string>
#include "Image.h"
#include <memory>

class SceneTitle;

class ButtonGameStart : public Button
{
private:
	std::shared_ptr<Image> m_image;
	std::string m_text;
	int m_frameCount;
	// こうやってボタンごとに個別に設定していいのだろうか（主に開発速度的に）
	SceneTitle& m_titleRef;
public:
	ButtonGameStart(Vector2 initPos, SceneTitle& title);

	void NormalUpdate() override;
	void ForcusedUpdate() override;

	void Onpressed() override;

	void Draw() const override;
};