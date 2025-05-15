#include "ImageObject.h"
#include "Image.h"
#include <DxLib.h>
#include "Vector2.h"
#include <string>
#include "Camera.h"

ImageObject::ImageObject(Camera& camera, const Vector2& initPos, const std::string& graphPath) :
	GameObject(initPos),
	m_camera(camera)
{
	m_image = std::make_shared<Image>(graphPath);
}

void ImageObject::Update()
{
}

void ImageObject::Draw() const
{
	Vector2 drawPos = m_camera.Capture(m_pos);
	m_image->Draw(drawPos);
}

void ImageObject::SetGraph(const int& handle)
{
	m_image->SetGraph(handle);
}

void ImageObject::SetGraph(const std::string& path)
{
	m_image->SetGraph(path);
}

void ImageObject::ExpandGtaph(const float& exRate)
{
	m_image->ExpandGraph(exRate);
}

void ImageObject::SetExRate(const float& value)
{
	m_image->SetExRate(value);
}

void ImageObject::RotateGraph(const float& deg)
{
	m_image->RotateGraph(deg);
}

void ImageObject::SetAngle(const float& angleDeg)
{
	m_image->SetAngle(angleDeg);
}

void ImageObject::SetImageBlendMode(const int& blendmode, const int& pal)
{
	m_image->SetImageBlendMode(blendmode, pal);
}

void ImageObject::SetImageBlendMode(const int& blendMode)
{
	m_image->SetImageBlendMode(blendMode);
}

void ImageObject::SetImageBlendPal(const int& pal)
{
	m_image->SetImageBlendPal(pal);
}