#pragma once
#include "GameObject.h"
#include <memory>

class Camera;
class BoxCollider;
class Animation;
class Player;

class DestructibleBlock : public GameObject
{
private:
	std::shared_ptr<BoxCollider> m_col;

	std::shared_ptr<Animation> m_nowAnim;
	std::shared_ptr<Animation> m_normalAnim;
	std::shared_ptr<Animation> m_breakingAnim;

	// 今回は全部カメラの参照を持っているので慣例に従うが、次があればDrawに渡す形で実装する
	Camera& m_camera;
	Player& m_player;

	using State_t = void (DestructibleBlock::*) ();
	State_t m_state;

	void Normal();
	void Breaking();
public:
	DestructibleBlock(Camera& camera, const Vector2& initPos, Player& player);

	void Update() override;
	void Draw() const override;
};

