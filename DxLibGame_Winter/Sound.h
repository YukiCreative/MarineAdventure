#pragma once
#include <string>

// ‰¹
class Sound
{
private:
	int m_handle;
	int m_playType;
public:
	Sound(const std::string& fileName);
	~Sound();

	void Loop(const bool& value);
	void Play() const;
	void Stop() const;
	bool IsPlaying() const;
	void SetVolume(int param) const;
};

