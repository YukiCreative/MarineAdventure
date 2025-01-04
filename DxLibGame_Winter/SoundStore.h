#pragma once
#include <string>
#include <unordered_map>

// 音声ファイルを一括で読み込んでおく
// シングルトンにしちゃうゾ
class SoundStore
{
private:
	SoundStore();
	SoundStore(const SoundStore&) = delete;
	void operator=(const SoundStore&) = delete;

	std::unordered_map<std::string, int> m_store;
public:
	~SoundStore();

	static SoundStore& GetInstance();

	int GetSound(const std::string& fileName);
};

