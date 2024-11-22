#pragma once
#include <array>

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
	std::array<int, 168> m_imageArray = {};
	/// <summary>
	/// マップチップの元
	/// </summary>
	int m_sourceHandle;
public:
	/// <summary>
	/// デストラクタ
	/// 読んだ画像の片付け
	/// </summary>
	~MapImageStore();

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
};

