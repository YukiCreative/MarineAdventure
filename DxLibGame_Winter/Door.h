#pragma once
#include "GameObject.h"
#include <string>
#include <unordered_map>
#include "Vector2.h"
#include <memory>

// プロトタイプ宣言ってどこに書けばいいんだろう
class Image;
class Camera;
class CircleCollider;
class Player;

// マップの移動に使う
class Door : public GameObject
{
private:
	std::shared_ptr<Image> m_image;
	std::shared_ptr<CircleCollider> m_collider;

	std::string m_path;
	Vector2 m_nextPlayerPos;

	Camera& m_camera;
	Player& m_player;

	bool CheckInDoor() const;
	void In();
protected:
	Door(Player& player, Camera& camera, const Vector2& initPos, const std::string& path, const Vector2& nextPlayerPos);

	virtual void Entry() = 0;
public:
	void Update() override;
	void Draw() const override;
};

