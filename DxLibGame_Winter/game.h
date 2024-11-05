#pragma once

namespace Game
{
	// 定数にはkを先頭に付ける
	// mとかsとかkとかを先頭に付けると
	// 予測が出やすいね！ 
	//constexpr int kScreenWidth = 1280;
	//constexpr int kScreenHeight = 720; // 16:9いつもの
	//constexpr int kScreenWidth = 640;
	//constexpr int kScreenHeight = 480; // 昔のブラウン管の比率らしい DXLibのデフォルト
	constexpr int kScreenWidth = 1280;
	constexpr int kScreenHeight = 720; // 個人的に推奨
	constexpr int kColorBitNum = 32;

	constexpr bool kDefaultWindowMode = true;
}