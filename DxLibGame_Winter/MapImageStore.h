#pragma once
#include <array>

namespace
{
	constexpr int kImageNum = 256;
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
	/// マップチップのハンドルを集める
	/// </summary>
	std::array<int, kImageNum> m_imageArray = {};
	/// <summary>
	/// マップチップの元
	/// </summary>
	int m_sourceHandle;
	// 背景装飾用
	int m_backSourceHandle;
	std::array<int, 4 * 4> m_backImageArray;
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
	int GetBackGraph(int id) const;
};

