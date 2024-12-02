#pragma once

/// <summary>
/// 敵や動かせるブロックなど、
/// オブジェクト全部を一意な値で列挙したもの
/// </summary>
enum class ObjectKind
{
	kEmpty = 0,
	kHarmFish,
	kMax,
};