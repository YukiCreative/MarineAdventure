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

	// ����͑S���J�����̎Q�Ƃ������Ă���̂Ŋ���ɏ]�����A���������Draw�ɓn���`�Ŏ�������
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

