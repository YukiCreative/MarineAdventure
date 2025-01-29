#include "TileImage.h"
#include "ImageStore.h"

TileImage::TileImage(const std::string& fileName) :
	m_handle(-1),
	m_graphSize(),
	m_exRate(2.5f)
{
	SetImage(fileName);
}

void TileImage::Draw(const Vector2& leftTop, const Vector2& rightBottom) const
{
	const int imageSizeX = static_cast<int>(m_graphSize.x * m_exRate);
	const int imageSizeY = static_cast<int>(m_graphSize.x * m_exRate);

	const Vector2 drawRect = rightBottom - leftTop;
	// �摜�̑傫���ƕ`��͈͂���J��Ԃ��񐔂�����o���ĂԂ�񂵂ďI���
	const int widthLoopNum   = static_cast<int>(drawRect.x) / imageSizeX;
	const int heightLoopNum  = static_cast<int>(drawRect.y) / imageSizeY;
	const int widthImageGap  = static_cast<int>(drawRect.x) % m_graphSize.x;
	const int heightImageGap = static_cast<int>(drawRect.y) % m_graphSize.y;

	for (int y = 0; y < heightLoopNum; ++y)
	{
		for (int x = 0; x < widthLoopNum; ++x)
		{
			DrawRotaGraphF(imageSizeX * 0.5f + leftTop.x + x * imageSizeX, imageSizeY * 0.5f + leftTop.y + y * imageSizeY, static_cast<double>(m_exRate), 0.0, m_handle, true);
		}
	}
}

void TileImage::SetImage(const std::string& fileName)
{
	// �摜�ƁA���̃T�C�Y���擾
	int x, y;
	m_handle = ImageStore::GetInstance().GetGraph(fileName);
	GetGraphSize(m_handle, &x, &y);
	m_graphSize.x = x;
	m_graphSize.y = y;
}
