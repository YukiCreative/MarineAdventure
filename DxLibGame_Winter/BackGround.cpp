#include "BackGround.h"
#include <DxLib.h>

BackGround::BackGround()
{
	m_graphHandle = LoadGraph("Data/Image/ŠC”wŒi.jpg");
}

void BackGround::Update()
{

}

void BackGround::Draw() const
{
	
	DrawGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), m_graphHandle, false);
}
