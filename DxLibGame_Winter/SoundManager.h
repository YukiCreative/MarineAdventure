#pragma once
#include <list>
#include <string>
#include <memory>

class Sound;

class SoundManager
{
private:
	SoundManager();
	SoundManager(const SoundManager&) = delete;
	void operator=(const SoundManager&) = delete;

	using SoundList_t = std::list<std::shared_ptr<Sound>>;
	SoundList_t m_sounds;

	// �ꊇ�ŕς�����
	// 0(����)~255(�f�t�H���g)
	void SetSoundVolume(int volume);
public:
	static SoundManager& GetInstance();

	// ���t���[���Ăяo��
	void Update();

	void RemoveFinishedSounds();
	// Unity��Instantiate�݂����Ȋ����ŁA����������ɂ��̎Q�Ƃ�Ԃ�
	std::weak_ptr<Sound> Play(const std::string& fileName);
};

