#include "Music.h"
#include <DxLib.h>
#include <algorithm>

namespace
{
	constexpr int kVolumeMin = 0;
	constexpr int kVolumeMax = 255;
}

Music::Music() :
	m_playType(DX_PLAYTYPE_LOOP)
{
}

Music& Music::GetInstance()
{
	static Music instance;
	return instance;
}

void Music::Play(const std::string& path) const
{
	PlayMusic(path.c_str(), m_playType);
}

void Music::Loop(const bool& loopOrNot)
{
	m_playType = loopOrNot ? DX_PLAYTYPE_LOOP : DX_PLAYTYPE_BACK;
}

void Music::SetVolume(const int& volume)
{
	 int vol = std::clamp(volume, kVolumeMin, kVolumeMax);
	 SetVolumeMusic(vol);
}

bool Music::IsPlaying() const
{
	return CheckMusic();
}

void Music::Stop() const
{
	StopMusic();
}
