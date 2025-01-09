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
	// Image��������
	m_image = std::make_shared<Image>(-1);
	m_sourceHandle = ImageStore::GetInstance().GetGraph(fileName);
	// �摜�T�C�Y���AoneImageSize�Ŋ���؂�邩���ׂ�
	Vector2Int graphSize;
	GetGraphSize(m_sourceHandle, &graphSize.x, &graphSize.y);
	assert(!(graphSize.x % oneImageSize.x) && "�^����ꂽ�T�C�Y�ŉ��������Ă݂����Ǘ]�肪�o����");
	// �R�}���̕������摜���L���ł���悤�ɂ���
	m_frameHandle.resize(graphSize.x / oneImageSize.x);
	for (int x = 0; auto& graph : m_frameHandle)
	{
		graph = DerivationGraph(x * oneImageSize.x, 0, oneImageSize.x, oneImageSize.y, m_sourceHandle);
		++x;
	}
	// ����Ȃ�ł�����
	m_allAnimNum = static_cast<int>(m_frameHandle.size());
	// �S�̃t���[��
	m_allFrame = m_oneAnimTime * m_allAnimNum;
}

void Animation::Update()
{
	// �t���[����i�߂�
	++m_frameCount;
	if (m_frameCount >= m_allFrame)
	{
		m_frameCount = 0;
	}

	// ���݂̉摜�̔ԍ������߂�
	m_nowAnimNum = m_frameCount / m_oneAnimTime;
}

void Animation::Draw(const Vector2& pos) const
{
	// ���݂̉摜�ԍ��ɂ���ĉ摜��؂�ւ���
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
