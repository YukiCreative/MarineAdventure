#include "BackGround.h"
#include "Image.h"
#include <DxLib.h>
#include "Vector2.h"
#include <string>
#include "Camera.h"

BackGround::BackGround(Camera& camera, const Vector2& initPos, const std::string& graphPass) :
	GameObject(initPos),
	m_camera(camera)
{
	m_image = std::make_shared<Image>(graphPass);
}

void BackGround::Update()
{
	// ˆÚ“®
	m_pos += m_velocity;
	m_velocity = Vector2::Zero();
}

void BackGround::Draw() const
{
	Vector2 drawPos = m_camera.Capture(m_pos);
	m_image->Draw(drawPos);
}

void BackGround::SetGraph(const int& handle)
{
	m_image->SetGraph(handle);
}

void BackGround::SetGraph(const std::string& pass)
{
	m_image->SetGraph(pass);
}

void BackGround::ExpandGtaph(const float& exRate)
{
	m_image->ExpandGraph(exRate);
}

void BackGround::SetExRate(const float& value)
{
	m_image->SetExRate(value);
}

void BackGround::RotateGraph(const float& deg)
{
	m_image->RotateGraph(deg);
}

void BackGround::SetAngle(const float& angleDeg)
{
	m_image->SetAngle(angleDeg);
}

void BackGround::SetImageBlendMode(const int& blendmode, const int& pal)
{
	m_image->SetImageBlendMode(blendmode, pal);
}

void BackGround::SetImageBlendMode(const int& blendMode)
{
	m_image->SetImageBlendMode(blendMode);
}

void BackGround::SetImageBlendPal(const int& pal)
{
	m_image->SetImageBlendPal(pal);
}