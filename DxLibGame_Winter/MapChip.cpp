#include "MapChip.h"
#include <DxLib.h>
#include "game.h"
#include "BoxCollider.h"
#include "Camera.h"
#include "MapConstants.h"
#include "ObjectsController.h"
#include "MapSystem.h"
#include "Player.h"
#include "MapImageStore.h"
#include "Image.h"
#include "Animation.h"

namespace
{
	const std::string kMarineAnimPath = "MarineMapAnimation.png";
	constexpr int kMarineAnimImageSize = 32;
	constexpr float kMarineExRate = MapConstants::kChipSize / kMarineAnimImageSize;
}

void kMapChip::ResetMapData()
{
	// マップデータに問い合わせてマップ情報をもらう
	m_mapChipData = m_system.GetMapChipData(m_mapPos);
	// 画像
	m_chipImage->SetGraph(m_mapChipData.graphHandle);
	m_backImage->SetGraph(m_mapChipData.backGraphHandle);

	// もしこの位置のオブジェクトが出せるなら出す
	if (m_objectsController.CanSpawnObject(m_mapPos))
	{
		m_objectsController.SpawnObject(m_mapChipData.objKind, m_pos, m_mapPos);
	}

	// 線分の当たり判定を設定する
	// 周りのコライダーが有効でない->自分は有効
	m_collider->SetIsLineValid(LineDir::Top,    !m_system.GetMapChipCollidable(Vector2Int(m_mapPos.x,     m_mapPos.y - 1))); // 上
	m_collider->SetIsLineValid(LineDir::Bottom, !m_system.GetMapChipCollidable(Vector2Int(m_mapPos.x,     m_mapPos.y + 1))); // 下
	m_collider->SetIsLineValid(LineDir::Left,   !m_system.GetMapChipCollidable(Vector2Int(m_mapPos.x - 1, m_mapPos.y))); // 左
	m_collider->SetIsLineValid(LineDir::Right,  !m_system.GetMapChipCollidable(Vector2Int(m_mapPos.x + 1, m_mapPos.y))); // 右
}

bool kMapChip::LoopScreen()
{
	// 自分の座標が特定の範囲外に出てたら
	// 反対側に瞬間移動
	// 上と左方向が優先(でないと1フレームのうちに反復横跳びする)
	// 短絡評価によって実装している
	return CheckLoopUpAndLeft() || CheckLoopDownAndRight(); // Checkとか名前付いてるけどがっつりメンバ変数いじってます。ごめんなさい。
}

bool kMapChip::CheckLoopUpAndLeft()
{
	// スクリーン座標を計算
	Vector2 screenPos = m_camera.Capture(m_pos);
	// 画面外判定
	bool isLoop = false;
	if (screenPos.x <= -MapConstants::kChipOffset) // 左から右へ
	{
		// ループの式ってこんなのになるんだ
		m_pos.x += Game::kScreenWidth + MapConstants::kChipOffset * 2;
		m_mapPos.x += MapConstants::kWidthChipNum;
		isLoop = true;
	}
	if (screenPos.y <= -MapConstants::kChipOffset) // 上から下へ
	{
		m_pos.y += Game::kScreenHeight + MapConstants::kChipOffset * 2;
		m_mapPos.y += MapConstants::kHeightChipNum;
		isLoop = true;
	}
	return isLoop;
}

bool kMapChip::CheckLoopDownAndRight()
{
	// スクリーン座標を計算
	Vector2 screenPos = m_camera.Capture(m_pos);
	bool isLoop = false;
	if (screenPos.y >= Game::kScreenHeight + MapConstants::kChipOffset) // 下から上へ
	{
		m_pos.y -= Game::kScreenHeight + MapConstants::kChipOffset * 2;
		m_mapPos.y -= MapConstants::kHeightChipNum;
		isLoop = true;
	}
	if (screenPos.x >= Game::kScreenWidth + MapConstants::kChipOffset) // 右端から左端へ
	{
		m_pos.x -= Game::kScreenWidth + MapConstants::kChipOffset * 2;
		m_mapPos.x -= MapConstants::kWidthChipNum;
		isLoop = true;
	}
	return isLoop;
}

kMapChip::kMapChip(Camera& camera, ObjectsController& cont, const Vector2 initPos, const Vector2Int initMapPos, MapSystem& system) :
	GameObject(initPos),
	m_camera(camera),
	m_objectsController(cont),
	m_mapPos(initMapPos),
	m_system(system)
{
	m_collider        = std::make_shared<BoxCollider>(m_pos, MapConstants::kChipSize, MapConstants::kChipSize);
	m_chipImage       = std::make_shared<Image>      (-1);
	m_backImage       = std::make_shared<Image>      (-1);
	m_marineAnimation = std::make_shared<Animation>  ();

	m_chipImage->SetExRate(MapConstants::kExRate);
	m_backImage->SetExRate(MapConstants::kExRate);
	m_marineAnimation->Init(kMarineAnimPath, 32, 30);
	m_marineAnimation->SetExRate(kMarineExRate);
	m_marineAnimation->SetBlendMode(DX_BLENDMODE_ALPHA, 128);

	ResetMapData();
}

void kMapChip::Update()
{
	// 処理の順序は移動→ループ判定
	m_pos += m_movePos;

	// 瞬間移動を試して、起こったら画像を再取得
	if (LoopScreen())
	{
		ResetMapData();
		//printf("ループ！！");
		printf("MapPos:x=%d,y=%d\n", m_mapPos.x, m_mapPos.y);
	}

	// movePosを0,0でリセット
	m_movePos = Vector2();

	m_marineAnimation->Update();
}

void kMapChip::Draw() const
{
	Vector2 drawPos = m_camera.Capture(m_pos);
	m_backImage->Draw(drawPos);

	if (m_mapChipData.environment == MapConstants::Environment::kWater)
	{
		m_marineAnimation->Draw(drawPos);
	}

	m_chipImage->Draw(drawPos);

#if _DEBUG
	DrawPixel(static_cast<int>(drawPos.x), static_cast<int>(drawPos.y), 0xff0000);
	DrawFormatString(static_cast<int>(drawPos.x) - 20, static_cast<int>(drawPos.y), 0xff0000, "X;%d\nY:%d", m_mapPos.x, m_mapPos.y);

	m_collider->DrawColliderRange_Debug(m_camera.DrawOffset());
#endif
}

bool kMapChip::CanCollide() const
{
	// これ変えたいな
	return m_chipImage->GraphHandle() != -1;
}

MapChipData kMapChip::GetMapChipData() const
{
	return m_mapChipData;
}

void kMapChip::ChangeGraph_Debug()
{
	m_chipImage->SetGraph(MapImageStore::GetInstance().GetGraph(158));
}
