#pragma once
#include "GameObject.h"
#include <memory>

class Animation;

// ¡‚ÌƒRƒCƒ“æ“¾—Ê‚ğ•\¦‚·‚é‚¾‚¯
class CoinUI : public GameObject
{
private:
	std::shared_ptr<Animation> m_coinAnim;
	int m_fontHandle;
public:
	CoinUI(const Vector2& initPos);
	~CoinUI();

	void Update() override;
	void Draw() const override;
};

