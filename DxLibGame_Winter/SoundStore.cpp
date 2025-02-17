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
    // 指定したフォルダ内にある音声ファイルを全読み込み
    namespace fs = std::filesystem;

    for (const auto& file : fs::directory_iterator(kFolderPath))
    {
        std::string path = file.path().string();
        // ファイル名を取り出す
        std::string pathCopy = path;
        std::string fileName = pathCopy.erase(0, kFolderPath.size());
        m_store[fileName] = LoadSoundMem(path.c_str());
#if _DEBUG
        assert(m_store[fileName] != -1 && "音声ファイル読み込みに失敗した");
        printf("音声ファイルを読み込みました。\n");
        printf("　ファイル名：%s\n", fileName.c_str());
        printf("　ハンドル：%d\n", m_store[fileName]);
#endif
    }
}

SoundStore::~SoundStore()
{
    // 音声ファイルの全削除
    InitSoundMem();
}

SoundStore& SoundStore::GetInstance()
{
    static SoundStore instance;
    return instance;
}

int SoundStore::GenerateSound(const std::string& fileName)
{
    assert(m_store.contains(fileName) && "与えられたパスの音声が無いよ");
    return DuplicateSoundMem(m_store.at(fileName));
}
