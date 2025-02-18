#pragma once
#include "Enemy.h"
#include <memory>

class CircleCollider;
class Image;
class Player;
class Camera;
class ObjectsController;

// Ç†ÇΩÇÈÇ∆É_ÉÅÅ[ÉW
class SeaUrchin : public Enemy
{
private:
	std::shared_ptr<CircleCollider> m_col;
	std::shared_ptr<Image> m_image;
public:
	SeaUrchin(ObjectsController& cont, const Vector2& initPos, Camera& camera, Player& player,const Vector2Int& mapPos);

	void Update() override;
	void Draw() const override;
};

