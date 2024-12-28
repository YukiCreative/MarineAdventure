#include "ImageStore.h"
#include <unordered_map>
#include <string>
#include <DxLib.h>
#include <filesystem>
#include <cassert>
#include <typeinfo>

namespace
{
    const std::string kFolderpath = "Data/Image/";
}

ImageStore::ImageStore()
{
    namespace fs = std::filesystem;

    // ここでこのゲームで使う画像を一括で読み込んでしまおう
    // 指定したフォルダの中のすべての画像ファイルを読み込む
    for (const auto& file : fs::directory_iterator(kFolderpath))
    {
        std::string path = file.path().string();
        m_store[path] = LoadGraph(path.c_str());
        printf("%d\n", m_store[path]);
        assert(m_store[path] != -1 && "画像ではないファイル形式が混入している可能性があります");
        printf("%s\n", path.c_str());
    }
    for (const auto& pair : m_store)
    {
        printf("%s :", typeid(pair.first).name());
        printf("%d\n", pair.second);
    }
}

ImageStore::~ImageStore()
{
    // 楽
    InitGraph();
}

ImageStore& ImageStore::GetInstance()
{
    static ImageStore instance;
    return instance;
}

int ImageStore::GetGraph(const std::string& id) const
{
    assert(m_store.contains(id) && "与えられたパスの画像が無いよ");
    return m_store.at(id);
}
