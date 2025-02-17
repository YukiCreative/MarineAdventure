#pragma once
#include <unordered_map>
#include <string>

/// <summary>
/// Data/Image�̒��̉摜�t�@�C����S�ǂݍ��݂���
/// </summary>
class ImageStore
{
private:
	ImageStore();
	ImageStore(const ImageStore&) = delete;
	void operator=(const ImageStore&) = delete;

	std::unordered_map<std::string, int> m_store;
public:
	~ImageStore();

	static ImageStore& GetInstance();

	int GetGraph(const std::string& fileName) const;
};