#include "SoundStore.h"
#include <filesystem>
#include <DxLib.h>
#include <cassert>

namespace
{
    const std::string kFolderPath = "Data/Sound/";
}

SoundStore::SoundStore()
{
    // �w�肵���t�H���_���ɂ��鉹���t�@�C����S�ǂݍ���
    namespace fs = std::filesystem;

    for (const auto& file : fs::directory_iterator(kFolderPath))
    {
        std::string path = file.path().string();
        // �t�@�C���������o��
        std::string pathCopy = path;
        std::string fileName = pathCopy.erase(0, kFolderPath.size());
        m_store[fileName] = LoadSoundMem(path.c_str());
#if _DEBUG
        assert(m_store[fileName] != -1 && "�����t�@�C���ǂݍ��݂Ɏ��s����");
        printf("�����t�@�C����ǂݍ��݂܂����B\n");
        printf("�@�t�@�C�����F%s\n", fileName.c_str());
        printf("�@�n���h���F%d\n", m_store[fileName]);
#endif
    }
}

SoundStore::~SoundStore()
{
    // �����t�@�C���̑S�폜
    InitSoundMem();
}

SoundStore& SoundStore::GetInstance()
{
    static SoundStore instance;
    return instance;
}

int SoundStore::GenerateSound(const std::string& fileName)
{
    assert(m_store.contains(fileName) && "�^����ꂽ�p�X�̉�����������");
    return DuplicateSoundMem(m_store.at(fileName));
}
