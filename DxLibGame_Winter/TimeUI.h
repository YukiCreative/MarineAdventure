#pragma once
#include "GameObject.h"
class TimeUI : public GameObject
{
private:
	int m_fontHandle;
public:
	TimeUI(const Vector2& initPos);
	~TimeUI();

	void Update() override;
	void Draw() const override;
};

