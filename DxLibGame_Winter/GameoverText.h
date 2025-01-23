#pragma once
#include "Vector2.h"
#include <array>

class ImageObject;

namespace
{
	constexpr int kTextNum = 8;
}

// �Q�[���I�[�o�[�̂��߂̃e�L�X�g
// ���������p�����Ȃ�
class GameoverText
{
private:
	Vector2 m_pos;
	int m_frameCount;

	// �ꕶ�����摜������
	// �\�肾��������߂邩��
	std::array<ImageObject, kTextNum> m_gameoverText;
public:
	GameoverText(const Vector2& initPos);

	void Update();
	void Draw() const;
};