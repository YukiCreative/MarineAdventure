#include "Animation.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "Camera.h"
#include "DestructibleBlock.h"
#include "Player.h"
#include "SoundManager.h"
#include "SceneController.h"
#include <string>

namespace
{
	constexpr int kBlockWidth = 80;
	constexpr int kBlockHeight = 80;
	constexpr int kBreakingAnimSize = 32;
	constexpr float kBreakImageExRate = static_cast<float>(kBlockWidth) / kBreakingAnimSize;
	const std::string kNormalAnimFile = "Block(32x32).png";
	const std::string kBleakingAnimFile = "BlockBreaking.png";
	const std::string kBreakingSound = "BreakBlock.wav";
}

void DestructibleBlock::Normal()
{
	// めんどくさいので
	// こっちでプレイヤーとの当たり判定をする
	CollisionStatus collision = m_col->CheckHit(m_player.GetCollider());

	if (!collision.isCollide) return;

	// 攻撃されてたら壊れる
	if (m_player.CheckState(PlayerState::kAttack) || m_player.CheckState(PlayerState::kStrongAttack))
	{
		m_state = &DestructibleBlock::Breaking;
		m_nowAnim = m_breakingAnim;
		SoundManager::GetInstance().Play(kBreakingSound);
		return;
	}

	// 押し戻す
	m_player.Teleportation(m_player.GetPos() + collision.overlap);
}

void DestructibleBlock::Breaking()
{
	// アニメーションが終了したら、死ぬ
	if (m_nowAnim->LoopCount())
	{
		m_isDeleted = true;
	}
}

DestructibleBlock::DestructibleBlock(Camera& camera, Player& player, const Vector2& initPos, const Vector2Int& baseMapPos) :
	GameObject(initPos, baseMapPos),
	m_camera(camera),
	m_state(&DestructibleBlock::Normal),
	m_player(player)
{
	m_col = std::make_shared<BoxCollider>(m_pos, static_cast<float>(kBlockWidth), static_cast<float>(kBlockHeight));

	m_normalAnim = std::make_shared<Animation>();
	// これだけInitなの何とかしろ
	m_normalAnim->Init(kNormalAnimFile, Vector2Int(kBlockWidth, kBlockHeight), 1);

	m_breakingAnim = std::make_shared<Animation>();
	m_breakingAnim->Init(kBleakingAnimFile, Vector2Int(kBreakingAnimSize, kBreakingAnimSize), 3);
	m_breakingAnim->SetExRate(kBreakImageExRate);

	m_nowAnim = m_normalAnim;
}

void DestructibleBlock::Update()
{
	m_nowAnim->Update();
	(this->*m_state)();
}

void DestructibleBlock::Draw() const
{
	Vector2 drawPos = m_camera.Capture(m_pos);
	m_nowAnim->Draw(drawPos);
}