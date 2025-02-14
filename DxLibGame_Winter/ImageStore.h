#pragma once
#include <unordered_map>
#include <string>

/// <summary>
/// Data/Imageの中の画像ファイルを全読み込みする
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