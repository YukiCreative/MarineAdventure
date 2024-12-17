#include "MapImageStore.h"
#include <DxLib.h>
#include <cassert>
#include "ImageStore.h"

namespace
{
	constexpr int kChipSize = 16;
	// 繰り返し処理してほしい数を定数で書きます
	constexpr int kWidthChipNum = 12;
	constexpr int kHeightChipNum = 14;
}

MapImageStore::MapImageStore()
{
	// マップチップの画像を読んで、それを16x16に分割したやつも作る
	// 作ったハンドルは配列に入れる
	m_sourceHandle = ImageStore::GetInstance().GetGraph("Data/Image/MapChip.png");
	assert(m_sourceHandle != -1);
	for (int y = 0; y < kHeightChipNum; ++y)
	{
		for (int x = 0; x < kWidthChipNum; ++x)
		{
			int index = kWidthChipNum * y + x;
			m_imageArray[index] = 
				DerivationGraph(kChipSize * x, kChipSize * y, kChipSize, kChipSize, m_sourceHandle);
		}
	}
}

MapImageStore::~MapImageStore()
{
	// 画像の消去
	for (const auto& handle : m_imageArray)
	{
		// これでいけるはず
		DeleteGraph(handle);
	}
}

MapImageStore& MapImageStore::GetInstance()
{
	static MapImageStore instance;
	return instance;
}

int MapImageStore::GetGraph(int id) const
{
	return m_imageArray[id];
}