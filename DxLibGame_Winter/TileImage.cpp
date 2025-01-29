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
	const int imageSizeX = m_graphSize.x * m_exRate;
	const int imageSizeY = m_graphSize.x * m_exRate;

	const Vector2 drawRect = rightBottom - leftTop;
	// 画像の大きさと描画範囲から繰り返し回数を割り出してぶん回して終わり
	const int widthLoopNum   = (drawRect.x) / imageSizeX;
	const int heightLoopNum  = (drawRect.y) / imageSizeY;
	const int widthImageGap  = static_cast<int>(drawRect.x) % m_graphSize.x;
	const int heightImageGap = static_cast<int>(drawRect.y) % m_graphSize.y;

	for (int y = 0; y < heightLoopNum; ++y)
	{
		for (int x = 0; x < widthLoopNum; ++x)
		{
			DrawRotaGraph(imageSizeX * 0.5f + leftTop.x + x * imageSizeX, imageSizeY * 0.5f + leftTop.y + y * imageSizeY, static_cast<double>(m_exRate), 0.0, m_handle, true);
		}

		if (widthImageGap == 0) continue;
		// 余った部分を描画
		SetDrawBlendMode(DX_BLENDMODE_ADD, 100);
		DrawRectRotaGraph(widthImageGap + imageSizeX * widthLoopNum, imageSizeY * 0.5f + leftTop.y + y * imageSizeY, 0, 0, widthImageGap, imageSizeY, m_exRate, 0.0, m_handle, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

void TileImage::SetImage(const std::string& fileName)
{
	// 画像と、そのサイズを取得
	int x, y;
	m_handle = ImageStore::GetInstance().GetGraph(fileName);
	GetGraphSize(m_handle, &x, &y);
	m_graphSize.x = x;
	m_graphSize.y = y;
}
