#include "BackGround.h"
#include <DxLib.h>
#include <string>

BackGround::BackGround(const std::string& pass)
{
	m_graphHandle = LoadGraph(pass.c_str());
}

BackGround::~BackGround()
{
	DeleteGraph(m_graphHandle);
}

void BackGround::Update()
{

}

void BackGround::Draw() const
{
	
	DrawGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), m_graphHandle, false);
}

void BackGround::SetGraph(const std::string& pass)
{
	DeleteGraph(m_graphHandle);
	m_graphHandle = LoadGraph(pass.c_str());
}
