#pragma once
#include <list>
#include "GameObject.h"

// UI
// ���ݑ̗͂�����
class HitPointHeart : public GameObject
{
private:

public:
	void Update() override;
	void Draw() const override;
};

// �n�[�g���܂Ƃ߂Ď��s����
// ���₵����A���炵����
class HitPoints : public GameObject
{
private:
	std::list<HitPointHeart> m_hearts;
public:
	void Update() override;
	void Draw() const override;
};