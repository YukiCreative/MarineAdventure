#include "SmallCoin.h"
#include "Camera.h"
#include "Player.h"
#include "Animation.h"
#include "SceneController.h"
#include "SceneGame.h"
#include "ObjectsController.h"

namespace
{
	const std::string  kFile = "SmallCoin.png";
	const Vector2Int   kSize = { 16, 16 };
	constexpr int kPlaySpeed = 5;
	constexpr int kGetThreshold = 1000;

	const std::string kEffectFile = "CoinEffect.png";
	const Vector2Int kEffectImageSize = { 32, 32 };

}

SmallCoin::SmallCoin(Player& player, Camera& camera, const Vector2& initPos, ObjectsController& cont) :
	GameObject(initPos),
	m_player(player),
	m_camera(camera),
	m_cont(cont)
{
	m_anim = std::make_shared<Animation>();
	m_anim->Init(kFile, kSize, kPlaySpeed);

	// �L���b�V�����Ƃ�
	m_scene = SceneController::GetInstance().CurrentScene();
}

void SmallCoin::Update()
{
	m_anim->Update();

	Vector2 rerativeToPlayer = m_pos - m_player.GetPos();
	// �v���C���[���߂Â�����擾�ł���
	if (rerativeToPlayer.SqrMagnitude() > kGetThreshold)
	{
		// �G�t�F�N�g�o��
		m_cont.SpawnEffect(kEffectFile, kEffectImageSize, kPlaySpeed, m_pos);
		m_player.OnRecovery();
	}
}

void SmallCoin::Draw() const
{
	Vector2 drawPos = m_camera.Capture(m_pos);
	m_anim->Draw(drawPos);
}
