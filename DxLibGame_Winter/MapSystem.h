#pragma once
#include "Vector2.h"
#include <memory>
#include <array>

class MapChip;

/// <summary>
/// マップチップを並べる、
/// マップチップを動かす、
/// マップチップを適切に読み込む、
/// マップチップを必要な分だけ表示する
/// </summary>
class MapSystem
{
private:
	/// <summary>
	/// 仮ですよ
	/// いずれはマップの素材を集めたクラスを作成しますよ
	/// </summary>
	int m_graphHandle;
	/// <summary>
	/// 横のマップチップの数
	/// このクラスのインスタンス化時に現在の画面サイズを見て決める
	/// </summary>
	int m_widthChipNum;
	/// <summary>
	/// 縦のマップチップの数
	/// </summary>
	int m_heightChipNum;
	Vector2 m_mapPos;
	std::array<std::shared_ptr<MapChip>, 16*9> m_mapChips;
public:
	MapSystem();

	/// <summary>
	/// 現在の描画場所に応じて表示するマップチップを判断
	/// </summary>
	void Update();
	/// <summary>
	/// マップチップを描画
	/// </summary>
	void Draw();

	/// <summary>
	/// マップチップの表示位置をずらす
	/// </summary>
	/// <param name="moveValue">現在の位置からどれだけ移動させるか</param>
	void MoveMap(Vector2 moveValue);
};

