#pragma once
#include <string>

class SoundManager;

// 音
class Sound
{
	friend SoundManager;

private:
	int m_handle;
	int m_playType;

	std::string m_fileName;

	// コンストラクタをプライベートにして、SoundManager以外のインスタンス化を禁止する
	Sound(const std::string& fileName);
public:
	~Sound();

	void Loop(const bool& value);
	void Play() const;
	void Stop() const;
	bool IsPlaying() const;
	void SetVolume(const int param) const;
};

