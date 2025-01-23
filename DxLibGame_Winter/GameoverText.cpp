#include "GameoverText.h"
#include "ImageObject.h"

GameoverText::GameoverText(const Vector2& initPos) :
	m_frameCount(0),
	m_pos(initPos)
{
	
}

void GameoverText::Update()
{
	++m_frameCount;
}

void GameoverText::Draw() const
{
}
