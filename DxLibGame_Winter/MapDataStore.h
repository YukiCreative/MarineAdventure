#pragma once
#include "Vector2.h"
#include "string"
#include <vector>
#include <memory>
#include "ObjectKind.h"

// マップのいろいろをまとめる
struct MapChipData
{
	int graphHandle;
	bool isCollidable;
	// 敵、ギミックなどオブジェクトの有無と種類を指し示す列挙体
	ObjectKind objKind;
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
	using MapVector_t = std::shared_ptr<std::vector<MapChipData>>;
	MapVector_t m_mapData;
public:

	// 文字通り
	// 古いマップデータはスマポで破棄される
	void LoadMapData(std::string pass);

	/// <summary>
	/// マップ座標からお目当てのマップチップのデータを返す
	/// </summary>
	/// <param name="id"></param>
	MapChipData GetMapData(Vector2Int mapPos);
};

