#pragma once
#include <string>
#include "Vector2.h"

class Text
{
private:
	std::string m_text;
	unsigned int m_color;
public:
	Text();
	Text(const std::string& initText);

	void Draw(const Vector2& drawPos);

	void SetText(const std::string& text) { m_text = text; }
};

