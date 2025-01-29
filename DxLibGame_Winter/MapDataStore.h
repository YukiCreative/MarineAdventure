#pragma once
#include "Vector2.h"
#include "string"
#include <vector>
#include <memory>
#include "MapConstants.h"
#include "MapChipData.h"

// どんなレイヤーがどんな順番であるか
enum class MapLayerAttribute
{
	kEnvironment,
	kBackDecoration,
	kMapChip,
	kObjects,
	kAttributeNum,
};

/// <summary>
/// 外部ファイルからマップのデータを読み込んで、
/// 持っていてくれるクラス
/// Sceneに持たせようかな
/// </summary>
class MapDataStore
{
private:
	//FMFヘッダー(Platinumのドキュメントに書いてある)
	struct Header
	{
		int8_t id[4];			//識別子(FMF_)		1*4バイト
		uint32_t size;			//データサイズ　		4バイト
		uint32_t mapWidth;		//マップの幅			4バイト
		uint32_t mapHeight;		//マップの高さ　		4バイト
		uint8_t chiphWidth;		//チップ(セル一個)の幅				1バイト
		uint8_t chpHeight;		//チップ(セル一個)の高さ				1バイト
		uint8_t layerCount;		//レイヤーの数						1バイト
		uint8_t bitCount;		//１セル当たりのビット数(÷8でバイト数)	1バイト
	};//20バイト

	// 今のマップデータのヘッダ情報を記憶しておく
	Header m_fmfHeader;

	// なげえ
	// めんどいからスタックに入れていい？
	// だめ
	using MapList_t = std::vector<std::vector<uint8_t>>;
	std::unique_ptr<MapList_t> m_mapData;
public:
	MapDataStore(const std::string& path);

	// 文字通り
	// 古いマップデータはスマポで破棄される
	void LoadMapData(const std::string& path);

	/// <summary>
	/// マップ座標からお目当てのマップチップのデータを返す
	/// </summary>
	/// <param name="id"></param>
	MapChipData GetMapData(const Vector2Int& mapPos) const;

	Vector2Int GetMapSize() const { return Vector2Int(m_fmfHeader.mapWidth, m_fmfHeader.mapHeight); }
	ObjectKind GetObjKind(const Vector2Int& mapPos) const;
	ObjectKind GetObjKind(const int& index) const;
};

