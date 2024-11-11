#pragma once
#include "Vector2.h"

/// <summary>
/// マップチップ一個分の画像を担当する
/// MapSystemがこれを固定配列で持つ
/// </summary>
class MapChip
{
private:
	/// <summary>
	/// 自分が今マップのどのチップを担当しているかを記憶
	/// </summary>
	Vector2 m_mapPos;

	/// <summary>
	/// 座標
	/// </summary>
	Vector2 m_graphPos;

	/// <summary>
	/// 動きを記憶
	/// </summary>
	Vector2 m_movePos;

	/// <summary>
	/// 画像のハンドル
	/// </summary>
	int m_graphHandle;

	/// <summary>
	/// 現在のマップのデータを参照して、
	/// 自分の持つグラフデータを決める
	/// </summary>
	void SetGraph();

	/// <summary>
	/// 自分が画面外に出ているかをチェックして、
	/// そうならば一周するかのように座標を移動させる
	/// </summary>
	/// <returns>true:画面外判定を通った false:画面内でした</returns>
	bool LoopScreen();
public:
	MapChip();

	/// <summary>
	/// 更新処理
	/// 画面外に出たら一周して戻ってきて
	/// 新しい画像を取得する
	/// </summary>
	void Update();

	/// <summary>
	/// これを描画
	/// </summary>
	void Draw();

	/// <summary>
	/// MapSystemから指示を受ける
	/// </summary>
	/// <param name="">現在地からどれだけ動かすか</param>
	void Move(Vector2 moveValue) { m_movePos += moveValue; }
};

