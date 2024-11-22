#pragma once
#include "Vector2.h"

/// <summary>
/// コライダーが計算した後に出てくるいろんな情報をひとまとめにして返したかった
/// </summary>
struct CollisionStatus
{
	// 当たっているか
	bool isCollide = false;
	// 当たった面に垂直に、どれくらいの向き、大きさでめり込んでいるかを出してくれます
	Vector2 overlap = Vector2::Zero();
};