#pragma once
#include <string>

class SoundManager;

// ��
class Sound
{
	friend SoundManager;

private:
	int m_handle;
	int m_playType;

	std::string m_fileName;

	// �R���X�g���N�^���v���C�x�[�g�ɂ��āASoundManager�ȊO�̃C���X�^���X�����֎~����
	Sound(const std::string& fileName);
public:
	~Sound();

	void Loop(const bool& value);
	void Play() const;
	void Stop() const;
	bool IsPlaying() const;
	void SetVolume(const int param) const;
};

