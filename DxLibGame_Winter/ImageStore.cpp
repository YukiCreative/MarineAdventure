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

    // �����ł��̃Q�[���Ŏg���摜���ꊇ�œǂݍ���ł��܂���
    // �w�肵���t�H���_�̒��̂��ׂẲ摜�t�@�C����ǂݍ���
    for (const auto& file : fs::directory_iterator(kFolderpath))
    {
        std::string path = file.path().string();
        m_store[path] = LoadGraph(path.c_str());
        printf("%d\n", m_store[path]);
        assert(m_store[path] != -1 && "��������������");
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
    // �y
    InitGraph();
}

ImageStore& ImageStore::GetInstance()
{
    static ImageStore instance;
    return instance;
}

int ImageStore::GetGraph(const std::string& id) const
{
    return m_store.at(id);
}
