#include "MapImageStore.h"
#include <DxLib.h>
#include <cassert>
#include "ImageStore.h"

namespace
{
	constexpr int kChipSize = 16;
	// �J��Ԃ��������Ăق�������萔�ŏ����܂�
	constexpr int kWidthChipNum = 12;
	constexpr int kHeightChipNum = 14;

	constexpr int kBackImageWidth = 4;
	constexpr int kBackImageHeight = 4;

	const std::string kMapImagePath = "MapChip.png";
	const std::string kBackImagePath = "BackImageMapParts.png";
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
	m_backSourceHandle = img.GetGraph(kBackImagePath);
	assert(m_sourceHandle != -1);
	for (int y = 0; y < kBackImageHeight; ++y)
	{
		for (int x = 0; x < kBackImageWidth; ++x)
		{
			int index = kBackImageWidth * y + x;
			m_backImageArray[index] =
				DerivationGraph(kChipSize * x, kChipSize * y, kChipSize, kChipSize, m_backSourceHandle);
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

int MapImageStore::GetBackGraph(int id) const
{
	return m_backImageArray[id];
}
