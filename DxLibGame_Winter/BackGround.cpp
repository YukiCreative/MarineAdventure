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
