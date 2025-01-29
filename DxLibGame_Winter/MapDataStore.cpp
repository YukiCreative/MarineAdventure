#include "MapDataStore.h"
#include <cassert>
#include "MapImageStore.h"
#include "ObjectKind.h"
#include <vector>
#include "MapConstants.h"
#include <Dxlib.h>

namespace
{
	constexpr int kLayerCount = 4;
	constexpr int kBitCount = 8;
	constexpr int kGraphInvisible = 0;
}

MapDataStore::MapDataStore(const std::string& path)
{
	m_mapData = std::make_unique<MapList_t>();
	LoadMapData(path);
}

void MapDataStore::LoadMapData(const std::string& path)
{
	int mapHandle = FileRead_open(path.c_str());
	// きまったバイト数を読み込む　これは変わらない
	// !!!!assertに関数を入れてはいけない!!!!
	int err = FileRead_read(&m_fmfHeader, sizeof(m_fmfHeader), mapHandle);
	assert(err != -1 && "ファイルの読み込みに失敗しました");

	// FMF_ってのをstrIDにぶち込んでる
	std::string strId;
	strId.resize(4);
	std::copy_n(m_fmfHeader.id, 4, strId.begin());
	// わざわざstringに写すのは、
	// 終端文字問題と、
	// エディタの警告を黙らせるためだと推測
	assert(strId == "FMF_" && "ファイル形式が不明です");
	assert(m_fmfHeader.bitCount == kBitCount && "ビットカウントは8しか対応できませぬ");
	assert(m_fmfHeader.layerCount == kLayerCount && "レイヤーは5層になりました");

	// 一つのレイヤーのバイト(=チップ)数を取得
	int layerDataSize = m_fmfHeader.mapWidth * m_fmfHeader.mapHeight * (m_fmfHeader.bitCount / 8);
	
	// レイヤー数*チップ数の要素を持たせる
	m_mapData->clear();
	m_mapData->resize(m_fmfHeader.layerCount);
	for (auto& tempLayerData : *m_mapData)
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

MapChipData MapDataStore::GetMapData(const Vector2Int& mapPos) const
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
		result.decorationGraphHandle = -1;
		result.backGroundHandle = -1;
		// 何もスポーンしない
		result.objKind = ObjectKind::kEmpty;
		// 一応水で
		result.environment = MapConstants::kEnvironment::kWater;
	}
	else
	{
		const int chipIndex = mapPos.y * m_fmfHeader.mapWidth + mapPos.x;
		const int graphNum  = static_cast<int>((*m_mapData)[static_cast<int>(MapLayerAttribute::kMapChip)][chipIndex]);
		// 環境
		result.environment           = static_cast<MapConstants::kEnvironment>((*m_mapData)[static_cast<int>(MapLayerAttribute::kEnvironment)][chipIndex]);
		// 出現するオブジェクト
		result.objKind               = static_cast<ObjectKind>((*m_mapData)[static_cast<int>(MapLayerAttribute::kObjects)][chipIndex]);
		// 背景画像
		result.decorationGraphHandle = imgStore.GetDecoGraph(static_cast<int>((*m_mapData)[static_cast<int>(MapLayerAttribute::kBackDecoration)][chipIndex]));
		result.backGroundHandle      = imgStore.GetBackGraph(static_cast<int>((*m_mapData)[static_cast<int>(MapLayerAttribute::kEnvironment)][chipIndex]));
		if (graphNum != kGraphInvisible)
		{
			result.graphHandle = imgStore.GetGraph(static_cast<int>((*m_mapData)[static_cast<int>(MapLayerAttribute::kMapChip)][chipIndex]));
		}
		else
		{
			// 画像番号kGraphInvisibleは特殊
			// 透明な画像ハンドルでもいいが、一意の値にしないと
			// チップ側で透明かどうかわからないという欠陥仕様
			// bool値でも持たせようかな
			result.graphHandle = -1;
		}
	}
	return result;
}

ObjectKind MapDataStore::GetObjKind(const Vector2Int& mapPos) const
{
	return static_cast<ObjectKind>((*m_mapData)[static_cast<int>(MapLayerAttribute::kObjects)][mapPos.x + mapPos.y * m_fmfHeader.chiphWidth]);
}

ObjectKind MapDataStore::GetObjKind(const int& index) const
{
	return static_cast<ObjectKind>((*m_mapData)[static_cast<int>(MapLayerAttribute::kObjects)][index]);
}
