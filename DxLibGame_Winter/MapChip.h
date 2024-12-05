#pragma once
#include "Vector2.h"
#include <memory>
#include "GameObject.h"
#include "ObjectKind.h"

class BoxCollider;
class Camera;
class ObjectsController;
class MapSystem;
class Player;

/// <summary>
/// マップチップ一個分の画像を担当する
/// MapSystemがこれを固定配列で持つ
/// </summary>
class MapChip : public GameObject
{
private:
	/// <summary>
	/// 自分が今マップのどのチップを担当しているかを記憶
	/// </summary>
	Vector2Int m_mapPos;
	/// <summary>
	/// 動きを記憶
	/// </summary>
	Vector2 m_movePos;
	/// <summary>
	/// 画像
	/// </summary>
	int m_graphHandle;
	/// <summary>
	/// 当たり判定
	/// </summary>
	std::shared_ptr<BoxCollider> m_collider;
	// カメラさん
	Camera& m_camera;
	// 敵を呼び出す
	ObjectsController& m_objectsController;
	MapSystem& m_system;
	/// <summary>
	/// 自分が画面外に出ているかをチェックして、
	/// そうならば一周するかのように座標を移動させる
	/// </summary>
	/// <returns>true:画面外判定を通った false:画面内でした</returns>
	bool LoopScreen();
	bool CheckLoopUpAndLeft();
	bool CheckLoopDownAndRight();

	/// <summary>
	/// 現在のマップのデータを参照して、
	/// 自分の持つグラフデータを決める
	/// </summary>
	void ResetMapData();
public:
	// 引数がすんごい
	MapChip(Camera& camera, ObjectsController& cont, const Vector2 initPos, const Vector2Int initMapPos, MapSystem& system);

	/// <summary>
	/// 更新処理
	/// 画面外に出たら一周して戻ってきて
	/// 新しい画像を取得する
	/// </summary>
	void Update() override;

	/// <summary>
	/// これを描画
	/// </summary>
	void Draw() const override;

	/// <summary>
	/// MapSystemから指示を受ける
	/// </summary>
	/// <param name="">現在地からどれだけ動かすか</param>
	void Move(Vector2 moveValue) { m_movePos += moveValue; }

	/// <summary>
	/// 座標返す
	/// </summary>
	/// <returns>座標</returns>
	Vector2 GetPos() const { return m_pos; }

	/// <summary>
	/// 返すだけ
	/// なんか受け渡しが面倒になってきたな
	/// </summary>
	/// <returns>マップチップのコライダー</returns>
	BoxCollider& GetCollider() const { return *m_collider; }

	bool CanCollide() const;

	void ChangeGraph_Debug();
};

