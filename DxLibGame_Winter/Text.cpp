#include "Text.h"
#include <DxLib.h>

Text::Text() :
	m_color(0xffffff)
{
}

Text::Text(const std::string& initText) :
	m_color(0xffffff)
{
}

void Text::Draw(const Vector2& drawPos)
{
	//DrawFormatStringToHandle(drawPos.x, drawPos.y, m_color, );
}
