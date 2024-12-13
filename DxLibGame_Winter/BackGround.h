#pragma once
#include "GameObject.h"
#include <string>

/// <summary>
/// 背景画像を表示したい
/// 遠景なので手前(マップチップ、プレイヤー)よりゆっくり動かしたい
/// </summary>
class BackGround : public GameObject
{
private:
	int m_graphHandle;
public:
	BackGround(const std::string& pass);
	~BackGround();

	void Update() override;
	void Draw() const override;

	void SetGraph(const int& handle) { m_graphHandle = handle; }
	void SetGraph(const std::string&);
};

