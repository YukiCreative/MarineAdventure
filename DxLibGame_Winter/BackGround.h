#pragma once
#include "GameObject.h"
#include <memory>
#include <string>
#include "Vector2.h"

class Image;
class Camera;

// ”wŒi‰æ‘œ‚ğ•\¦‚µ‚½‚¢
class ImageObject : public GameObject
{
private:
	std::shared_ptr<Image> m_image;
	Camera& m_camera;
	// 1ƒtƒŒ[ƒ€‚Ì’†‚ÅˆÚ“®—Ê‚ğ‹L‰¯
	Vector2 m_velocity;
public:
	ImageObject(Camera& camera, const Vector2& initPos, const std::string& path);

	void Update() override;
	void Draw() const override;

	void Move(Vector2 amount) { m_velocity += amount; };
	// Image‚ÌŠÖ”‚ğ‚»‚Ì‚Ü‚Üˆø‚«Œp‚®
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

