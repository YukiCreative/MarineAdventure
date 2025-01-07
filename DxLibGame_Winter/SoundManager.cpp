#include "SoundManager.h"
#include "Sound.h"

SoundManager::SoundManager()
{
}

void SoundManager::SetSoundVolume(int volume)
{
	for (auto& sound : m_sounds)
	{
		// こっちでバリデーションチェックしてくれるから大丈夫っしょ
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
	// これでええやん
	SoundList_t playingSounds;
	for (const auto& sound : m_sounds)
	{
		if (sound->IsPlaying())
		{
			playingSounds.push_back(sound);
		}
	}
	// 再生中のだけ残して後は参照しない→解放
	m_sounds = playingSounds;

	//printf("今の音源インスタンス：%d個\n", m_sounds.size());
}

std::weak_ptr<Sound> SoundManager::Play(const std::string& fileName)
{
	// SoundManagerをfriend登録してプライベートのコンストラクタを呼び出している
	std::shared_ptr<Sound> sound(new Sound(fileName));
	m_sounds.push_back(sound);
	sound->Play();
	return sound;
}
