#pragma once
#include <string>

class Music
{
private:
	Music();
	Music(const Music&) = delete;
	void operator=(const Music&) = delete;

	int m_playType;
public:
	static Music& GetInstance();
	void Play(const std::string& path) const;
	void Loop(const bool& loopOrNot);
	// 0~255
	void SetVolume(const int& volume);
	bool IsPlaying() const;
	void Stop() const;
};