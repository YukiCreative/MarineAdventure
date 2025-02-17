#pragma once
#include "GameObject.h"
#include <memory>

// 一つのクラスで複数の雲を扱いたいという不純な動機
enum class CloudKind
{
	k1,
	k2
};

class Animation;
class Camera;

// アニメーションするだけ
class Cloud : public GameObject
{
private:
	Camera& m_camera;
	std::shared_ptr<Animation> m_anim;
public:
	Cloud(Camera& camera, const Vector2& initPos, const CloudKind kind = CloudKind::k1);

	void Update() override;
	void Draw() const override;
};

