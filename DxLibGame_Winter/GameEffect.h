#pragma once
#include "GameObject.h"
#include <memory>
#include <string>

class Animation;

// ���̓A�j���[�V���������������������̃Q�[���I�u�W�F�N�g
class GameEffect : public GameObject
{
private:
	std::shared_ptr<Animation> m_animation;
	std::weak_ptr<GameObject>  m_followGameObject;
	bool    m_isLoop;
	Vector2 m_offset;
	float m_exRate;
public:
	GameEffect(const std::string& filename, const Vector2Int& oneImageSize, const int& playSpeed, const Vector2& initPos, const Vector2& offset = Vector2::Zero());

	void Update() override;
	void Draw() const override;

	void Loop(const bool& loopOrNot) { m_isLoop = loopOrNot; }
	void SetExRate(const float value);

	// ������ �R���X�g�Q�Ƃ͂��Ȃ�
	void SetFollowGameObject(std::shared_ptr<GameObject> object) { m_followGameObject = object; }
	void ResetFollowObject() { m_followGameObject.reset(); }
};