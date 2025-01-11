#pragma once
#include <algorithm>

// �l�͈̔͂�0~255�̂�����int
// �揜�͗v��Ȃ�����
struct Volume
{
	const int kMaxValue = 255;
	const int kMinValue = 0;

	int value;

	void operator=(const Volume& right) { value = right.value; }
	Volume(int _value)
	{
		value = std::clamp(_value, kMinValue, kMaxValue);
	}

	Volume operator+(const Volume& right) { return Volume(value + right.value); }
	Volume operator-(const Volume& right) { return Volume(value - right.value); }
};

// ���ʂ�����
// �O��������肷��
// �I�v�V��������w�����󂯂ĉ��ʂ̒l��ύX������A�t�@�C���ɕۑ�������
// �V���O���g���ɂ͂��Ȃ��Ă�������
// �O���[�o���͂ł��邾�����炵������
class VolumeLoader
{
public:
	// �O���ɕۑ�����Ă��鉹�ʂ�ǂݍ���
	Volume LoadMasterVolume();
	Volume LoadMusicVolume();
	Volume LoadSoundVolume();
};