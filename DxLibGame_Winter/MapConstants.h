#pragma once

// マップシステムに使う定数が複数のコードで似通ってきたので
// 独立して統合的にヘッダ化した
namespace MapConstants
{
	constexpr float kChipSize = 80.0f;
	constexpr int kImageSize = 16;
	constexpr float kExRate = static_cast<float>(kChipSize) / static_cast<float>(kImageSize);
	// 現時点でのマップチップの一辺の半分のピクセル
	// DrawRectGraphは画像の中心が原点なのでこうなる
	constexpr int kChipOffset = static_cast<int>(kChipSize * 0.5f);
	// w17,h10ぐらいがちょうどいいんすわ
	constexpr int kWidthChipNum = 1;
	constexpr int kHeightChipNum = 1;
}