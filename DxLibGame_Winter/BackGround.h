#pragma once
#include "GameObject.h"
#include <memory>
#include <string>
#include "Vector2.h"

class Image;
class Camera;

// �w�i�摜��\��������
class ImageObject : public GameObject
{
private:
	std::shared_ptr<Image> m_image;
	Camera& m_camera;
	// 1�t���[���̒��ňړ��ʂ��L��
	Vector2 m_velocity;
public:
	ImageObject(Camera& camera, const Vector2& initPos, const std::string& path);

	void Update() override;
	void Draw() const override;

	void Move(Vector2 amount) { m_velocity += amount; };
	// Image�̊֐������̂܂܈����p��
	void SetGraph(const int& handle);
	void SetGraph(const std::string& path);
	void ExpandGtaph(const float& exRate);
	void SetExRate(const float& value);
	void RotateGraph(const float& deg);
	void SetAngle(const float& angleDeg);
	void SetImageBlendMode(const int& blendmode, const int& pal);
	void SetImageBlendMode(const int& blendMode);
	void SetImageBlendPal(const int& pal);
};

