#include "VolumeLoader.h"
#include "Music.h"
#include <string>
#include <fstream>
#include <sstream>
#include <cassert>

namespace
{
	// テキストファイルから読み込む形にしようかな
	// バイナリはよくわからんし、手動で書き換えたいかもしれないし
	const std::string kFilePath = "Data/Config/Volume.txt";
}

void VolumeLoader::ResetVolumeConfig()
{
	for (auto& volume : m_volumes)
	{
		volume.Reset();
	}
}

Volume VolumeLoader::LoadVolume()
{
	std::ifstream file(kFilePath);
	assert(file && "ファイルが開けてない");

	std::string data;

	for (auto& volume : m_volumes)
	{
		std::getline(file, data);
		std::stringstream ss(data);

		int temp;
		ss >> temp;

		volume = temp;
	}

	//return Volume();
	return 255;
}

Volume VolumeLoader::SoundVolume() const
{
	return Volume();
}

Volume VolumeLoader::MusicVolume() const
{
	return Volume();
}

void VolumeLoader::SaveVolume()
{
	std::ofstream saveFile(kFilePath);

	for (const auto& volume : m_volumes)
	{
		saveFile << volume.value;
	}
}