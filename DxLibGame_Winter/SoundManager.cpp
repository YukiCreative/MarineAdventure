#include "SoundManager.h"
#include "Sound.h"

SoundManager::SoundManager()
{
}

void SoundManager::SetSoundVolume(int volume)
{
	for (auto& sound : m_sounds)
	{
		// �������Ńo���f�[�V�����`�F�b�N���Ă���邩����v������
		sound->SetVolume(volume);
	}
}

SoundManager& SoundManager::GetInstance()
{
	static SoundManager instance;
	return instance;
}

void SoundManager::Update()
{
	RemoveFinishedSounds();
}

void SoundManager::RemoveFinishedSounds()
{
	// ����ł������
	SoundList_t playingSounds;
	for (const auto& sound : m_sounds)
	{
		if (sound->IsPlaying())
		{
			playingSounds.push_back(sound);
		}
	}
	// �Đ����̂����c���Č�͎Q�Ƃ��Ȃ������
	m_sounds = playingSounds;

	//printf("���̉����C���X�^���X�F%d��\n", m_sounds.size());
}

std::weak_ptr<Sound> SoundManager::Play(const std::string& fileName)
{
	// SoundManager��friend�o�^���ăv���C�x�[�g�̃R���X�g���N�^���Ăяo���Ă���
	std::shared_ptr<Sound> sound(new Sound(fileName));
	m_sounds.push_back(sound);
	sound->Play();
	return sound;
}
