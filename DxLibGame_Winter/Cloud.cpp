#include "Animation.h"
#include "Camera.h"
#include "Cloud.h"
#include <cassert>
#include <string>
#include <unordered_map>

namespace
{
	const std::string kImageFile1 = "cloud1.png";
	const std::string kImageFile2 = "cloud2.png";

	const Vector2Int  kImageSize1 = { 64, 64 };
	const Vector2Int  kImageSize2 = { 64, 64 };
	constexpr int     kPlaySpeed  = 10;
}

Cloud::Cloud(Camera& camera, const Vector2& initPos, const CloudKind kind):
	GameObject(initPos, DrawPriority::kBehind),
	m_camera(camera)
{
	m_anim = std::make_shared<Animation>();
	// めんどいので条件分岐
	switch (kind)
	{
	case (CloudKind::k1):
		m_anim->Init(kImageFile1, kImageSize1, kPlaySpeed);
		break;
	case (CloudKind::k2):
		m_anim->Init(kImageFile2, kImageSize2, kPlaySpeed);
		break;
	default:
		assert(false && "雲の初期化種類が網羅できてない");
		break;
	}
	// とりあえずでかくしとこ
	m_anim->SetExRate(2.0f);
}

void Cloud::Update()
{
	// カメラを参照して、少し動く
	// 遠くにあるイメージ
	const Vector2 cameraVel = m_camera.GetVel();
	m_pos += cameraVel * 0.5f;
	m_anim->Update();
}

void Cloud::Draw() const
{
	const Vector2 drawPos = m_camera.Capture(m_pos);
	m_anim->Draw(drawPos);
}
