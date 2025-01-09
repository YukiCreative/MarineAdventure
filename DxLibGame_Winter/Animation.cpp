#include "Animation.h"
#include "Image.h"
#include <memory>
#include "Vector2.h"
#include <cassert>
#include "ImageStore.h"

Animation::Animation() :
	m_allAnimNum(0),
	m_allFrame(0),
	m_frameCount(0),
	m_image(nullptr),
	m_nowAnimNum(0),
	m_sourceHandle(-1),
	m_oneAnimTime(0)
{
}

void Animation::Init(const std::string& fileName, const Vector2Int& oneImageSize, const int& playSpeed)
{
	m_oneAnimTime = playSpeed;
	// Imageを初期化
	m_image = std::make_shared<Image>(-1);
	m_sourceHandle = ImageStore::GetInstance().GetGraph(fileName);
	// 画像サイズが、oneImageSizeで割り切れるか調べる
	Vector2Int graphSize;
	GetGraphSize(m_sourceHandle, &graphSize.x, &graphSize.y);
	assert(!(graphSize.x % oneImageSize.x) && "与えられたサイズで横分割してみたけど余りが出たよ");
	// コマ数の分だけ画像を記憶できるようにする
	m_frameHandle.resize(graphSize.x / oneImageSize.x);
	for (int x = 0; auto& graph : m_frameHandle)
	{
		graph = DerivationGraph(x * oneImageSize.x, 0, oneImageSize.x, oneImageSize.y, m_sourceHandle);
		++x;
	}
	// こんなんでいいや
	m_allAnimNum = static_cast<int>(m_frameHandle.size());
	// 全体フレーム
	m_allFrame = m_oneAnimTime * m_allAnimNum;
}

void Animation::Update()
{
	// フレームを進める
	++m_frameCount;
	if (m_frameCount >= m_allFrame)
	{
		m_frameCount = 0;
	}

	// 現在の画像の番号を求める
	m_nowAnimNum = m_frameCount / m_oneAnimTime;
}

void Animation::Draw(const Vector2& pos) const
{
	// 現在の画像番号によって画像を切り替える
	m_image->SetGraph(m_frameHandle[m_nowAnimNum]);
	m_image->Draw(pos);
}

void Animation::SetExRate(const float& rate)
{
	m_image->SetExRate(rate);
}

void Animation::SetBlendMode(const int& mode, const int& param)
{
	m_image->SetImageBlendMode(mode, param);
}

void Animation::ReverceX(const bool& value)
{
	m_image->SetReverceFlagX(value);
}
