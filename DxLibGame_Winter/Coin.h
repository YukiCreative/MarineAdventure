#pragma once
#include "GameObject.h"
#include "Vector2.h"
#include <string>
#include <memory>

class Player;
class Camera;
class Animation;

class SmallCoin : public GameObject
{
private:
	std::shared_ptr<Animation> m_anim;
	Player& m_player;
	Camera& m_camera;
public:
	SmallCoin(Player& player, Camera& camera, const Vector2& initPos);

	void Update() override;
	void Draw() const override;
};

