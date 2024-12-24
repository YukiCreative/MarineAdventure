#pragma once
#include "Scene.h"

// このクラスにさせたいこと
// オプションシーンへ
// タイトルに戻る
// 装飾用の画像
class PauseScene : public Scene
{
private:
public:
	void Update() override;
	void Draw() const override;
};

