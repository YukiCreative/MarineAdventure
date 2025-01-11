#pragma once
#include <algorithm>

// 値の範囲が0~255のただのint
// 乗除は要らないかな
struct Volume
{
	const int kMaxValue = 255;
	const int kMinValue = 0;

	int value;

	void operator=(const Volume& right) { value = right.value; }
	Volume(int _value)
	{
		value = std::clamp(_value, kMinValue, kMaxValue);
	}

	Volume operator+(const Volume& right) { return Volume(value + right.value); }
	Volume operator-(const Volume& right) { return Volume(value - right.value); }
};

// 音量を持つ
// 外部から入手する
// オプションから指示を受けて音量の値を変更したり、ファイルに保存したり
// シングルトンにはしなくていいかな
// グローバルはできるだけ減らしたいし
class VolumeLoader
{
public:
	// 外部に保存されている音量を読み込む
	Volume LoadMasterVolume();
	Volume LoadMusicVolume();
	Volume LoadSoundVolume();
};