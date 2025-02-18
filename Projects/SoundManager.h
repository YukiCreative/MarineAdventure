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

	// 一括で変えられる
	// 0(無音)~255(デフォルト)
	void SetSoundVolume(int volume);
public:
	static SoundManager& GetInstance();

	// 毎フレーム呼び出す
	void Update();

	void RemoveFinishedSounds();
	// UnityのInstantiateみたいな感じで、生成した後にその参照を返す
	std::weak_ptr<Sound> Play(const std::string& fileName);
};

