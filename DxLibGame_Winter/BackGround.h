#pragma once
#include "GameObject.h"

/// <summary>
/// 背景画像を表示したい
/// 遠景なので手前(マップチップ、プレイヤー)よりゆっくり動かしたい
/// </summary>
class BackGround : public GameObject
{
private:
	int m_graphHandle;
public:
	BackGround();

	void Update() override;
	void Draw() const override;
};

