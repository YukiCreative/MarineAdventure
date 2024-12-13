#pragma once
#include "GameObject.h"
#include <memory>
#include <string>
#include "Vector2.h"

class Image;
class Camera;

// 背景画像を表示したい
class BackGround : public GameObject
{
private:
	std::shared_ptr<Image> m_image;
	Camera& m_camera;
	// 1フレームの中で移動量を記憶
	Vector2 m_velocity;
public:
	BackGround(Camera& camera, const Vector2& initPos, const std::string& pass);

	void Update() override;
	void Draw() const override;

	void Move(Vector2 amount) { m_velocity += amount; };
};

