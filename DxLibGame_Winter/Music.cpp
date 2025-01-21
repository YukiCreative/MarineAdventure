#include "Music.h"
#include <DxLib.h>
#include <algorithm>
#include "VolumeLoader.h"

Music::Music() :
	m_playType(DX_PLAYTYPE_LOOP),
	m_nowPlayingFilePath(),
	m_volume(255)
{
	m_volume = VolumeLoader::LoadMusicVolume();
	SetVolume(m_volume);
}

Music& Music::GetInstance()
{
	static Music instance;
	return instance;
}

void Music::Play(const std::string& path)
{
	// ó¨ÇªÇ§Ç∆ÇµÇƒÇ¢ÇÈâπäyÇ™ìØÇ∂ìzÇ»ÇÁÅAÇªÇÃÇ‹Ç‹Ç…ÇµÇΩÇ©Ç¡ÇΩÇÒÇ≈Ç∑
	if (m_nowPlayingFilePath == path) return;

	m_nowPlayingFilePath = path;
	PlayMusic(path.c_str(), m_playType);
	SetVolumeMusic(m_volume.value);
}

void Music::Loop(const bool& loopOrNot)
{
	m_playType = loopOrNot ? DX_PLAYTYPE_LOOP : DX_PLAYTYPE_BACK;
}

void Music::SetVolume(const Volume& volume)
{
	m_volume = volume;
	SetVolumeMusic(volume.value);
}

bool Music::IsPlaying() const
{
	return CheckMusic();
}

void Music::Stop() const
{
	StopMusic();
}
