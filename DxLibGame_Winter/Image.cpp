#include "Image.h"
#include <DxLib.h>
#include <string>
#include "Vector2.h"
#include "ImageStore.h"

Image::Image(const int& handle) :
	m_expandRate  (1.0f),
	m_angle       (0.0f),
	m_blendMode   (DX_BLENDMODE_NOBLEND),
	m_blendPal    (0),
	m_sourceHandle(handle),
	m_reverceX    (false),
	m_reverceY    (false),
	m_offset	  ()
{
}

Image::Image(const std::string& path) :
	m_expandRate(1.0f),
	m_angle     (0.0f),
	m_blendMode (DX_BLENDMODE_NOBLEND),
	m_blendPal  (0),
	m_reverceX  (false),
	m_reverceY  (false),
	m_offset	()
{
	m_sourceHandle = ImageStore::GetInstance().GetGraph(path);
}

void Image::Draw(const Vector2& pos) const
{
	Vector2 correctedPos = pos + m_offset;
	SetDrawBlendMode(m_blendMode, m_blendPal);
	DrawRotaGraph(static_cast<int>(correctedPos.x), static_cast<int>(correctedPos.y), static_cast<double>(m_expandRate),
		static_cast<double>(m_angle), m_sourceHandle, true, m_reverceX, m_reverceY);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Image::SetGraph(const std::string& path)
{
	m_sourceHandle = ImageStore::GetInstance().GetGraph(path);
}