#include "MapDataStore.h"
#include <cassert>

void MapDataStore::LoadMapData(std::string pass)
{
	int handle = FileRead_open(pass.c_str());
	// きまったバイト数を読み込む　これは変わらない
	FileRead_read(&m_fmfHeader, sizeof(m_fmfHeader), handle);

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

	// 一つのレイヤーのバイト数を取得
	int layerDataSize = m_fmfHeader.mapWidth * m_fmfHeader.mapHeight * (m_fmfHeader.bitCount / 8);
	// 今後すること
	// 1.バイナリ読み込み
	// 　8ビットか16ビットかで型を使い分ける（ささやかなコピペじゃないアピール）
	// 　MapData構造体にぶち込む
	// 　レイヤーが二つある前提で、ぶち込む
	// 　↑これをスマートに繰り返し処理したい
}

MapChipData MapDataStore::GetMapData(Vector2Int mapPos)
{
	return MapChipData();
}
