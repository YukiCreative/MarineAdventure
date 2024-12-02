#pragma once

// �}�b�v�V�X�e���Ɏg���萔�������̃R�[�h�Ŏ��ʂ��Ă����̂�
// �Ɨ����ē����I�Ƀw�b�_������
namespace MapConstants
{
	constexpr float kChipSize = 80.0f;
	constexpr int kImageSize = 16;
	constexpr float kExRate = static_cast<float>(kChipSize) / static_cast<float>(kImageSize);
	// �����_�ł̃}�b�v�`�b�v�̈�ӂ̔����̃s�N�Z��
	// DrawRectGraph�͉摜�̒��S�����_�Ȃ̂ł����Ȃ�
	constexpr int kChipOffset = static_cast<int>(kChipSize * 0.5f);
	// w17,h10���炢�����傤�ǂ����񂷂�
	constexpr int kWidthChipNum = 1;
	constexpr int kHeightChipNum = 1;
}