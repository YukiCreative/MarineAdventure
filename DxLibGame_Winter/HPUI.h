#pragma once
#include <list>
#include "GameObject.h"

// UI
// 現在体力を現す
class HitPointHeart : public GameObject
{
private:

public:
	void Update() override;
	void Draw() const override;
};

// ハートをまとめて実行する
// 増やしたり、減らしたり
class HitPoints : public GameObject
{
private:
	std::list<HitPointHeart> m_hearts;
public:
	void Update() override;
	void Draw() const override;
};