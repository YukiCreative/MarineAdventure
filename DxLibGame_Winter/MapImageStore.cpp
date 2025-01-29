#include "MapImageStore.h"
#include <DxLib.h>
#include <cassert>
#include "ImageStore.h"

namespace
{
	constexpr int kChipSize      = 16;
	constexpr int kBackChipSize  = 32;
	// �J��Ԃ��������Ăق�������萔�ŏ����܂�
	constexpr int kWidthChipNum  = 16;
	constexpr int kHeightChipNum = 16;

	constexpr int kDecoImageWidth  = 4;
	constexpr int kDecoImageHeight = 4;

	constexpr int kBackPartsWidth  = 2;
	constexpr int kBackPartsHeight = 1;

	const std::string kMapImagePath   = "MapChip.png";
	const std::string kDecoImagePath  = "BackImageMapParts.png";
	const std::string kBackGroundPath = "MapBackGround.png";
}

MapImageStore::MapImageStore()
{
	ImageStore& img = ImageStore::GetInstance();

	// �}�b�v�`�b�v�̉摜��ǂ�ŁA�����16x16�ɕ�������������
	// ������n���h���͔z��ɓ����
	m_sourceHandle = img.GetGraph(kMapImagePath);
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

	// ��Ƃقړ���
	m_decorationSourceHandle = img.GetGraph(kDecoImagePath);
	assert(m_decorationSourceHandle != -1);
	for (int y = 0; y < kDecoImageHeight; ++y)
	{
		for (int x = 0; x < kDecoImageWidth; ++x)
		{
			int index = kDecoImageWidth * y + x;
			m_decoImageArray[index] =
				DerivationGraph(kChipSize * x, kChipSize * y, kChipSize, kChipSize, m_decorationSourceHandle);
		}
	}

	// ��Ƃقڂقړ���
	m_backGroundSourceHandle = img.GetGraph(kBackGroundPath);
	assert(m_backGroundSourceHandle != -1);
	for (int y = 0; y < kBackPartsHeight; ++y)
	{
		for (int x = 0; x < kBackPartsWidth; ++x)
		{
			int index = kBackPartsWidth * y + x;
			m_backImageArray[index] =
				DerivationGraph(kBackChipSize * x, kBackChipSize * y, kBackChipSize, kBackChipSize, m_backGroundSourceHandle);
		}
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

int MapImageStore::GetDecoGraph(int id) const
{
	return m_decoImageArray[id];
}

int MapImageStore::GetBackGraph(int id) const
{
	return m_backImageArray[id];
}
