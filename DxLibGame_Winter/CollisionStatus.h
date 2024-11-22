#pragma once
#include "Vector2.h"

/// <summary>
/// コライダーが計算した後に出てくるいろんな情報をひとまとめにして返したかった
/// </summary>
struct CollisionStatus
{
	// 当たっているか
	bool isCollide = false;
	// めり込んでいるところの一番長い距離
	// 当たっていれば大きさは正、そうでなければ負
	Vector2 overlap = Vector2::Zero();
	// 各自円とか四角形とかで頑張ってずるしながら出す
	// 単位ベクトル
	Vector2 normal = Vector2::Zero();
};