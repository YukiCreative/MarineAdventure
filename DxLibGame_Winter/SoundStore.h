#pragma once
#include <string>
#include <unordered_map>

// �����t�@�C�����ꊇ�œǂݍ���ł���
// �V���O���g���ɂ����Ⴄ�]
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

