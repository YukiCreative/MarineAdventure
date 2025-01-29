#pragma once

/// <summary>
/// 敵や動かせるブロックなど、
/// オブジェクト全部を一意な値で列挙したもの
/// </summary>
enum class ObjectKind
{
	kEmpty,
	kHarmFish,
	kBoss,
	kDestructibleBlock,
	kCloud1,
	kCloud2,
	// ほかにも追加したいオブジェクトがあるので、ドアを後ろに置いておく
	kDoor1 = 8, // これ(全部列挙)以外思いつかなかった
	kDoor2,
	kDoor3,
	kDoor4,
	kDoor5,
	kDoor6,
	kDoor7,
	kDoor8,
};