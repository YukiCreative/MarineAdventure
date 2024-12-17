#pragma once
#include <memory>
#include "Vector2.h"
#include <string>
#include <vector>

class Image;

// �A�j���[�V����
class Animation
{
private:
	// ���摜
	// �����摜�͈ꖇ�ň�̃A�j���[�V�����������Ă��āA�������Ɉ��ɕ���ł���z��
	int m_sourceHandle;
	// �����������
	std::vector<int> m_frameHandle;
	// �A�j���[�V�����̑���
	int m_allAnimNum;
	// �A�j���[�V�����I���܂ł̑��t���[��
	int m_allFrame;
	// ���̉摜�����Ԗڂ�
	int m_nowAnimNum;
	// �A�j���[�V�����̍Đ����x(���t���[���ŃA�j���[�V�������؂�ւ�邩)
	int m_oneAnimTime;
	int m_frameCount;
	std::shared_ptr<Image> m_image;
public:
	Animation() = default;

	/// <summary>
	/// �A�j���[�V������ݒ肷��ۂɁA�R���X�g���N�^�ł͂Ȃ�������ŏ���������
	/// </summary>
	/// <param name="path">�A�j���[�V�����摜�̃p�X</param>
	/// <param name="oneFrameSize">�摜��؂�T�C�Y</param>
	/// <param name="playSpeed">�Đ����x(�摜���؂�ւ��܂ŉ��t���[�������邩)</param>
	void Init(const std::string& path, const int& oneFrameSize, const int& playSpeed);

	void Update();
	void Draw(const Vector2& pos) const;

	void Stop();
};