#pragma once
#include "MapConstants.h"
#include "ObjectKind.h"

// DataStoreから分離
// マップのいろいろをまとめる
// 外部に渡す用
struct MapChipData
{
	int graphHandle;
	int backGraphHandle;
	// 敵、ギミックなどオブジェクトの有無と種類を指し示す列挙体
	ObjectKind objKind;
	// 地上or水中
	MapConstants::Environment environment;
};