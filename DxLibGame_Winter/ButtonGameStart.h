#pragma once
#include "Button.h"
#include <string>
#include "Image.h"
#include <memory>

class ButtonGameStart : public Button
{
private:
	std::shared_ptr<Image> m_image;
	std::string m_text;
public:
	void NormalUpdate() override;
	void ForcusedUpdate() override;

	void Onpressed() override;

	void Draw() const override;
};