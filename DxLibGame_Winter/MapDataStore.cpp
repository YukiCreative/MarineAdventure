#include "MapDataStore.h"
#include <cassert>
#include "MapImageStore.h"
#include "ObjectKind.h"
#include <vector>
#include "MapConstants.h"

namespace
{
	constexpr int kLayerCount = 2;
	constexpr int kBitCount = 8;
	constexpr int kGraphInvisible = 159;
}

MapDataStore::MapDataStore(std::string pass)
{
	LoadMapData(pass);
}

void MapDataStore::LoadMapData(std::string pass)
{
	int mapHandle = FileRead_open(pass.c_str());
	// きまったバイト数を読み込む　これは変わらない
	FileRead_read(&m_fmfHeader, sizeof(m_fmfHeader), mapHandle);
	assert(m_fmfHeader.bitCount == kBitCount && "ビットカウントは8しか対応できませぬ");
	assert(m_fmfHeader.layerCount == kLayerCount && "レイヤーは二層でございます");

	// FMF_ってのをstrIDにぶち込んでる
	std::string strId;
	strId.resize(4);
	std::copy_n(m_fmfHeader.id, 4, strId.begin());
	// わざわざstringに写すのは、
	// 終端文字問題と、
	// エディタの警告を黙らせるためだと推測
	if (strId != "FMF_") {
		assert(false && "「なにこのファイル」って言ってる。多分");
	}

	// 一つのレイヤーのバイト(=チップ)数を取得
	int layerDataSize = m_fmfHeader.mapWidth * m_fmfHeader.mapHeight * (m_fmfHeader.bitCount / 8);
	
	// レイヤー数*チップ数の要素を持たせる
	m_mapData.resize(m_fmfHeader.layerCount);
	for (auto& tempLayerData : m_mapData)
	{
		// 要素数を確保しーの
		tempLayerData.resize(layerDataSize);
		// ここで各レイヤーにデータをぶち込む
		// FileRead_readは続きから読み込むんだと思う
		int result = FileRead_read(tempLayerData.data(), layerDataSize, mapHandle);
		assert(result != -1 && "ファイル読み込み中に不具合");
	}
	// ここでファイルの役割は終わり
	FileRead_close(mapHandle);
}

MapChipData MapDataStore::GetMapData(Vector2Int mapPos)
{
	// ここでハンドルや列挙体など、使える形にしてしまう
	MapChipData result;
	MapImageStore& imgStore = MapImageStore::GetInstance();
	// マップの存在する範囲外ならば
	if (mapPos.x < 0 ||
		mapPos.y < 0 ||
		mapPos.x >= static_cast<int>(m_fmfHeader.mapWidth) ||
		mapPos.y >= static_cast<int>(m_fmfHeader.mapHeight))
	{
		// 何も画像を入れない->透明
		result.graphHandle = -1;
		// 何もスポーンしない
		result.objKind = ObjectKind::kEmpty;
	}
	else
	{
		const int chipIndex = mapPos.y * m_fmfHeader.mapWidth + mapPos.x;
		const int graphNum = static_cast<int>((m_mapData)[0][chipIndex]);
		if (graphNum != kGraphInvisible)
		{
			result.graphHandle = imgStore.GetGraph(static_cast<int>((m_mapData)[0][chipIndex]));
		}
		else
		{
			// 画像番号0は特殊
			// 透明な画像ハンドルでもいいが、一意の値にしないと
			// チップ側で透明かどうかわからないという欠陥仕様
			result.graphHandle = -1;
		}
		result.objKind = static_cast<ObjectKind>((m_mapData)[1][chipIndex]);
	}
	return result;
}
