#include "Animation.h"
#include "Image.h"
#include <memory>
#include "Vector2.h"
#include <cassert>
#include "ImageStore.h"

void Animation::Init(const std::string& path, const Vector2Int& oneFrameSize, const int& playSpeed)
{
	m_oneAnimTime = playSpeed;
	// Image��������
	m_image = std::make_shared<Image>(-1);
	m_sourceHandle = ImageStore::GetInstance().GetGraph(path);
	// �摜�T�C�Y���AoneFrameSize�Ŋ���؂�邩���ׂ�
	Vector2Int graphSize;
	GetGraphSize(m_sourceHandle, &graphSize.x, &graphSize.y);
	assert(!(graphSize.x % oneFrameSize.x) && "�^����ꂽ�T�C�Y�ŉ��������Ă݂����Ǘ]�肪�o����");
	// �R�}���̕������摜���L���ł���悤�ɂ���
	m_frameHandle.resize(graphSize.x / oneFrameSize.x);
	for (int x = 0; auto& graph : m_frameHandle)
	{
		graph = DerivationGraph(x * oneFrameSize.x, 0, oneFrameSize.x, oneFrameSize.y, m_sourceHandle);
		++x;
	}
	// ����Ȃ�ł�����
	m_allAnimNum = m_frameHandle.size();
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
