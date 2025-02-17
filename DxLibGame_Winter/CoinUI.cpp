#include "CoinUI.h"
#include "Animation.h"
#include "Statistics.h"
#include <DxLib.h>

namespace
{
	const std::string  kFile = "SmallCoin.png";
	const Vector2Int   kSize = { 16, 16 };
	constexpr int kPlaySpeed = 5;

	const Vector2Int kBoxSize = { 200, 50 };
	const std::string kText = "X %d";

	const Vector2 kAnimOffset = { 20, 0 };
	constexpr float kAnimExRate = 3.0f;

	const Vector2 kTextOffset = { 50, -10 };
	const std::string kFontPath = "Data/Font/07�ɂ��܂�t�H���g.otf";
	const std::string kFontName = "07�ɂ��܂�t�H���g";
	constexpr int kFontSize = 30;
	constexpr int kThickness = -1;
}

CoinUI::CoinUI(const Vector2& initPos) :
	GameObject(initPos)
{
	// ����̓Q�[�����̃R�C���Ɠ���
	m_coinAnim = std::make_shared<Animation>();
	m_coinAnim->Init(kFile, kSize, kPlaySpeed);
	m_coinAnim->SetExRate(kAnimExRate);

	AddFontResourceExA(kFontPath.c_str(), FR_PRIVATE, NULL);

	m_fontHandle = CreateFontToHandle(kFontName.c_str(), kFontSize, kThickness);
}

CoinUI::~CoinUI()
{
	// �ǂݍ��񂾃t�H���g�̍폜
	DeleteFontToHandle(m_fontHandle);
	RemoveFontResourceExA("", FR_PRIVATE, NULL);
}

void CoinUI::Update()
{
	m_coinAnim->Update();
}

void CoinUI::Draw() const
{
	// ���ɔ������̎l�p��`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawBox(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y - kBoxSize.y * 0.5f),
		static_cast<int>(m_pos.x + kBoxSize.x), static_cast<int>(m_pos.y + kBoxSize.y * 0.5f), 0xffffff, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// ���̏�Ƀt�H�[�}�b�g������
	Statistics& stats = Statistics::GetInstance();
	const int nowCoinTotal = stats.GetCoinNum() + stats.GetCoinNowStageNum();
	DrawFormatStringToHandle(static_cast<int>(m_pos.x + kTextOffset.x), static_cast<int>(m_pos.y + kTextOffset.y), 0xffffff, m_fontHandle, kText.c_str(), nowCoinTotal);

	m_coinAnim->Draw(m_pos + kAnimOffset);
}
