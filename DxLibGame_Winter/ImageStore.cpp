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
        // ���΃p�X�ł͂Ȃ��t�@�C���������Ŏ���悤�ɂ���
        std::string pathCopy = path;
        std::string fileName = pathCopy.erase(0, kFolderpath.size());
        m_store[fileName] = LoadGraph(path.c_str());
        assert(m_store[fileName] != -1 && "�摜�ł͂Ȃ��t�@�C���`�����������Ă���\��������܂�");
        printf("�摜�t�@�C����ǂݍ��݂܂���\n");
        printf("�@���΃p�X�F%s\n", path.c_str());
        printf("�@�L�[�F%s\n", fileName.c_str());
        printf("�@�n���h���F%d\n", m_store[fileName]);
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
    assert(m_store.contains(id) && "�^����ꂽ�p�X�̉摜��������");
    return m_store.at(id);
}
