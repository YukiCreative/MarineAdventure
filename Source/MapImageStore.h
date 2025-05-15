#pragma once
#include <array>

namespace
{
	constexpr int kChipSize = 16;
	// 繰り返し処理してほしい数を定数で書きます
	constexpr int kWidthChipNum = 16;
	constexpr int kHeightChipNum = 16;

	constexpr int kDecoImageWidth = 4;
	constexpr int kDecoImageHeight = 4;

	constexpr int kBackPartsWidth = 2;
	constexpr int kBackPartsHeight = 2;

	constexpr int kImageNum      = kWidthChipNum * kHeightChipNum;
	constexpr int kDecorationNum = kDecoImageWidth * kDecoImageHeight;
	constexpr int kBackGroundNum = kBackPartsWidth * kBackPartsHeight;
};

/// <summary>
/// マップチップの画像を一括で読み込んで管理するシングルトンクラス
/// </summary>
class MapImageStore
{
private:
	MapImageStore();
	MapImageStore(const MapImageStore&) = delete;
	void operator=(const MapImageStore&) = delete;

	/// <summary>
	/// マップチップの元
	/// </summary>
	int m_sourceHandle;
	// 背景装飾用
	int m_decorationSourceHandle;
	int m_backGroundSourceHandle;

	std::array<int, kImageNum> m_imageArray;
	std::array<int, kDecorationNum> m_decoImageArray;
	std::array<int, kBackGroundNum> m_backImageArray;
public:

	/// <summary>
	/// 毎度おなじみインスタンス取得
	/// </summary>
	/// <returns>インスタンスの参照</returns>
	static MapImageStore& GetInstance();

	/// <summary>
	/// MapIDを受け取って、それに該当する画像のハンドルを返す
	/// </summary>
	/// <param name="id">マップの通し番号をまとめた列挙体</param>
	/// <returns>該当するチップの画像のハンドル</returns>
	int GetGraph(int id) const;
	int GetDecoGraph(int id) const;
	int GetBackGraph(int id) const;
};

