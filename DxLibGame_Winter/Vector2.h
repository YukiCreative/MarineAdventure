#pragma once
#include <cmath>
#include <DxLib.h>
// ���̃X�N���v�g�ɂ͓��ɁA����include���Ȃ����ƁI

/// <summary>
/// �w�b�_�I�����[�̍\����
/// </summary>
struct Vector2
{
public:
	float x, y;

	Vector2() : x(0), y(0)
	{
	}

	Vector2(float _x, float _y) : x(_x), y(_y)
	{
	}

	// �ϊ��R���X�g���N�^
	// ���ꂪ���邨������float�Ƃ̉��Z�q�I�[�o�[���[�h�����Ȃ��čς�
	// (Vector2����邩�炿����ƒx���炵������)
	Vector2(float value) : x(value), y(value)
	{
	}

	// ����Vecor2���AVECTOR�������ꏊ�ɓ�������A�ÖٓI�ɕϊ������
	// DxLib�C���N���[�h���Ă邯�ǂ��傤���Ȃ�
	operator VECTOR()
	{
		return VGet(x, y, 0.0f);
	}

	/// <summary>
	/// ���ӂɁA�E�ӂ𑫂��Z�������̂���
	/// </summary>
	/// <param name="right">�E��</param>
	void operator+=(const Vector2& right)
	{
		x += right.x;
		y += right.y;
	}

	void operator-=(const Vector2& right)
	{
		x -= right.x;
		y -= right.y;
	}

	Vector2 operator*(const float& right) const
	{
		Vector2 result;
		result.x = x * x;
		result.y = y * y;
		return result;
	}

	void operator*=(const float& right)
	{
		x *= right;
		y *= right;
	}

	void operator/=(const float& right)
	{
		x /= right;
		y /= right;
	}

	Vector2 operator/(const float& right) const
	{
		Vector2 result;
		result.x = x / right;
		result.y = y / right;
		return result;
	}

	Vector2 operator+(const Vector2& other) const
	{
		Vector2 result;
		result.x = x + other.x;
		result.y = y + other.y;
		return result;
	}

	Vector2 operator-()
	{
		return Vector2(-x, -y);
	}

	// ����������I�[�o�[���[�h�H�c
	Vector2 operator-(const Vector2& other) const
	{
		Vector2 result;
		result.x = x - other.x;
		result.y = y - other.y;
		return result;
	}

	/// <summary>
	/// �傫���̓���Ԃ�
	/// </summary>
	/// <returns>�x�N�g���̑傫���̓��</returns>
	float SqrMagnitude()
	{
		return x * x + y * y;
	}

	/// <summary>
	///  �傫���Ԃ�
	/// </summary>
	/// <returns>�傫��</returns>
	float Magnitude()
	{
		return std::sqrtf(x * x + y * y);
	}

	/// <summary>
	/// ������P�ʃx�N�g���ɂ���
	/// </summary>
	void Normalize()
	{
		float mag = Magnitude();
		// �傫����0�Ȃ�return
		if (!mag) return;
		// �����̐����������̑傫���Ŋ���
		x = x / mag;
		y = y / mag;
	}

	/// <summary>
	/// �P�ʃx�N�g���ɂ����R�s�[��Ԃ�
	/// </summary>
	/// <returns>�P�ʃx�N�g��(�R�s�[)</returns>
	Vector2 GetNormalize()
	{
		Vector2 result;
		float mag = Magnitude();
		if (!mag) return *this;
		result.x = x / mag;
		result.y = y / mag;
		return result;
	}

	/// <summary>
	/// start����end�܂�rate���i�񂾃x�N�g����Ԃ�
	/// </summary>
	/// <param name="start">�����ʒu</param>
	/// <param name="end">�S�[��</param>
	/// <param name="rate">����0~1</param>
	/// <returns>start����end��rate���i�񂾃x�N�g��</returns>
	static Vector2 Lerp(const Vector2& start, const Vector2& end, const float& rate)
	{
		// std::clamp���g�����Ƃ������C���N���[�h���K�v�Ȃ̂Ŏ~�߂�
		float clampRate;
		if (rate < 0)
		{
			clampRate = 0;
		}
		else if (rate > 1)
		{
			clampRate = 1;
		}
		else
		{
			clampRate = rate;
		}
		Vector2 lerp = start;
		lerp += (end - start) * clampRate;
		return lerp;
	}

	// (0, 0)
	static Vector2 Zero()
	{
		return Vector2();
	}
	// (0, -1)
	static Vector2 Up()
	{
		return Vector2(0, -1);
	}
	// (0, 1)
	static Vector2 Down()
	{
		return Vector2(0, 1);
	}
	// (1, 0)
	static Vector2 Right()
	{
		return Vector2(1, 0);
	}
	// (-1, 0)
	static Vector2 Left()
	{
		return Vector2(-1, 0);
	}
};