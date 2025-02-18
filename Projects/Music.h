#pragma once
#include <string>
#include "VolumeLoader.h"

class Music
{
private:
	Music();
	Music(const Music&) = delete;
	void operator=(const Music&) = delete;

	int m_playType;
	Volume m_volume;

	std::string m_nowPlayingFilePath;
public:
	static Music& GetInstance();
	void Play(const std::string& path);
	void Loop(const bool& loopOrNot);
	// 0~255
	void SetVolume(const Volume& volume);
	bool IsPlaying() const;
	void Stop() const;
};