#pragma once
#include "game.h"

// �}�b�v�V�X�e���Ɏg���萔�������̃R�[�h�Ŏ��ʂ��Ă����̂�
// �Ɨ����ē����I�Ƀw�b�_������
namespace MapConstants
{
	constexpr float kChipSize = 80.0f;
	constexpr int kImageSize = 16;
	constexpr float kExRate = kChipSize / kImageSize;
	// �����_�ł̃}�b�v�`�b�v�̈�ӂ̔����̃s�N�Z��
	// DrawRectGraph�͉摜�̒��S�����_�Ȃ̂ł����Ȃ�
	constexpr int kChipOffset = static_cast<int>(kChipSize * 0.5f);
	// w17,h10���炢�����傤�ǂ����񂷂�
	constexpr int kWidthChipNum = static_cast<int>(Game::kScreenWidth / kChipSize) + 1;
	constexpr int kHeightChipNum = static_cast<int>(Game::kScreenHeight / kChipSize) + 1;

	// �n�ォ������
	enum class kEnvironment
	{
		kWater,
		kGround,
		kOutOfMap,
		kEnvNum,
	};
}