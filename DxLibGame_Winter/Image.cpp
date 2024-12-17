#include "Image.h"
#include <DxLib.h>
#include <string>
#include "Vector2.h"
#include "ImageStore.h"

Image::Image(const int& handle) :
	m_expandRate(1.0f),
	m_angle(0.0f),
	m_blendMode(DX_BLENDMODE_NOBLEND),
	m_blendPal(0),
	m_sourceHandle(handle)
{
}

Image::Image(const std::string& path) :
	m_expandRate(1.0f),
	m_angle(0.0f),
	m_blendMode(DX_BLENDMODE_NOBLEND),
	m_blendPal(0)
{
	m_sourceHandle = ImageStore::GetInstance().GetGraph(path);
}

void Image::Draw(const Vector2& pos) const
{
	SetDrawBlendMode(m_blendMode, m_blendPal);
	DrawRotaGraph(static_cast<int>(pos.x), static_cast<int>(pos.y), static_cast<double>(m_expandRate),
		static_cast<double>(m_angle), m_sourceHandle, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Image::SetGraph(const std::string& path)
{
	DeleteGraph(m_sourceHandle);
	m_sourceHandle = LoadGraph(path.c_str());
}