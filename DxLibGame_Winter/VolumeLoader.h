#pragma once
#include <algorithm>
#include <array>

enum class VolumeChannel
{
	kMaster,
	kSound,
	kMusic,
	kMax
};

// 値の範囲が0~255のただのint
// 乗除は要らないかな
struct Volume
{
	const int kMaxValue = 255;
	const int kMinValue = 0;

	int value;

	void operator=(const Volume& right) { value = right.value; }
	Volume() : value(kMaxValue) {}
	Volume(int _value)
	{
		value = std::clamp(_value, kMinValue, kMaxValue);
	}

	Volume operator+(const Volume& right) { return Volume(value + right.value); }
	Volume operator-(const Volume& right) { return Volume(value - right.value); }

	// 初期値(255)に戻す
	void Reset() { value = kMaxValue; }
};

// 音量を持つ
// 外部から入手する
// オプションから指示を受けて音量の値を変更したり、ファイルに保存したり
// シングルトンにはしなくていいかな
// グローバルはできるだけ減らしたいし
class VolumeLoader
{
private:
	std::array<Volume, static_cast<int>(VolumeChannel::kMax)> m_volumes;

	void ResetVolumeConfig();
public:
	// 外部に保存されている音量を読み込む
	Volume LoadVolume();

	// マスター音量を考慮したいい感じの音量を効果音やBGMに与える
	Volume SoundVolume() const;
	Volume MusicVolume() const;

	void SaveVolume();
};