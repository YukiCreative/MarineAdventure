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
        // 相対パスではなくファイル名だけで取れるようにする
        std::string pathCopy = path;
        std::string fileName = pathCopy.erase(0, kFolderpath.size());
        m_store[fileName] = LoadGraph(path.c_str());
        assert(m_store[fileName] != -1 && "画像ではないファイル形式が混入している可能性があります");
        printf("画像ファイルを読み込みました\n");
        printf("　相対パス：%s\n", path.c_str());
        printf("　キー：%s\n", fileName.c_str());
        printf("　ハンドル：%d\n", m_store[fileName]);
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

int ImageStore::GetGraph(const std::string& fileName) const
{
    assert(m_store.contains(fileName) && "与えられたパスの画像が無いよ");
    return m_store.at(fileName);
}
