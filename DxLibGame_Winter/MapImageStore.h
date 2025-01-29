#pragma once
#include <array>

namespace
{
	constexpr int kImageNum = 16 * 16;
	constexpr int kDecorationNum = 4 * 4;
	constexpr int kBackGroundNum = 2;
}

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

