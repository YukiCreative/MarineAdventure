#pragma once
#include "GameObject.h"
#include "Vector2.h"
#include <string>
#include <memory>

class Player;
class Camera;
class Animation;
class Scene;
class ObjectsController;

class SmallCoin : public GameObject
{
private:
	std::shared_ptr<Animation> m_anim;
	Player& m_player;
	Camera& m_camera;
	ObjectsController& m_cont;
	std::shared_ptr<Scene> m_scene;
public:
	SmallCoin(Player& player, Camera& camera, const Vector2& initPos, ObjectsController& cont);

	void Update() override;
	void Draw() const override;
};

