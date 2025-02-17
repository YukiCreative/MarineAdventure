#pragma once
#include "GameObject.h"
#include <memory>

// ��̃N���X�ŕ����̉_�����������Ƃ����s���ȓ��@
enum class CloudKind
{
	k1,
	k2
};

class Animation;
class Camera;

// �A�j���[�V�������邾��
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

