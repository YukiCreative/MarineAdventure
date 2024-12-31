#pragma once
#include "Scene.h"
#include <memory>
#include "Vector2.h"
#include <array>

class BoxCollider;
class CircleCollider;
class Collider;

/// <summary>
/// “–‚½‚è”»’è‚ÌƒeƒXƒg
/// </summary>
class ColliderTestScene : public Scene
{
private:
	int m_frameCount;
	std::shared_ptr<BoxCollider> boxCol;
	std::shared_ptr<BoxCollider> boxCol2;
	std::shared_ptr<CircleCollider> circleCol;
	std::shared_ptr<CircleCollider> circleCol2;
	unsigned int color;
	Vector2 boxPos = Vector2(500, 300);
	Vector2 boxPos2 = Vector2(300, 600);
	Vector2 boxHava = Vector2(128, 64);
	Vector2 circlePos = Vector2();
	Vector2 circlePos2 = Vector2(800, 100);
	Vector2* nowMousePos;
	std::shared_ptr<Collider> nowCol;
	std::array<std::shared_ptr<Collider>, 4> colArray;
	void HitKansuu();
	Vector2 overLap;
public:
	ColliderTestScene();
	~ColliderTestScene();

	void Entry() override {}
	virtual void NormalUpdate() override;
	virtual void Draw() const override;
};