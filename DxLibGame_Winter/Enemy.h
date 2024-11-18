#pragma once
#include "GameObject.h"

class Camera;

/// <summary>
/// “G‚ÌŠî’êƒNƒ‰ƒX
/// </summary>
class Enemy : public GameObject
{
private:
	// ‚Ù‚ñ‚Æ‚ÍGameObject‚É‚½‚¹‚½‚¢‚¯‚Ç
	// Camera‚àGameObject‚ÉŠÜ‚Ü‚ê‚é‚Ì‚Å’f”O
	Camera& m_camera;
protected:
	Enemy(Camera& camera) : m_camera(camera) {}

	// H‚ç‚¤
	virtual void Damage() = 0;
	// ‚¿‚Ê
	virtual void Death() = 0;
	// ‚à‚Ì‚Ç‚à‚ª‚©‚©‚éŠÖ”
	virtual void Attack() = 0;
public:
	// ‚±‚ê‚ç‚ÌŠÖ”‚Á‚ÄGameObject‚ÉˆÚ‚µ‚½‚Ù‚¤‚ª‚¢‚¢‚©‚È
	virtual void Update() = 0;
	virtual void Draw() = 0;
};

