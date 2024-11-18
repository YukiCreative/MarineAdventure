#pragma once
#include "GameObject.h"

class Camera;

/// <summary>
/// “G‚ÌŠî’êƒNƒ‰ƒX
/// </summary>
class Enemy : public GameObject
{
private:
	Camera& m_camera;
	int m_hp;
protected:
	Enemy(Camera& camera) :
		m_camera(camera),
		m_hp(0)
	{
	}

	// H‚ç‚¤
	virtual void Damage() = 0;
	// ‚¿‚Ê
	virtual void Death() = 0;
};

