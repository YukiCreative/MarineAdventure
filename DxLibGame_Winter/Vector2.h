#pragma once
#include <cmath>
// ���̃X�N���v�g�ɂ͓��ɁA����include���Ȃ����ƁI

/// <summary>
/// �w�b�_�I�����[�̍\����
/// </summary>
struct Vector2
{
public:
	float x, y;

	Vector2()
	{
		x = 0;
		y = 0;
	}

	Vector2(float _x, float _y)
	{
		x = _x;
		y = _y;
	}

	
	/// <summary>
	/// ���ӂɁA�E�ӂ𑫂��Z�������̂���
	/// </summary>
	/// <param name="right">�E��</param>
	void operator+=(Vector2 right)
	{
		x += right.x;
		y += right.y;
	}

	void operator-=(Vector2 right)
	{
		x -= right.x;
		y -= right.y;
	}

	void operator*=(Vector2 right)
	{
		x *= right.x;
		y *= right.y;
	}

	void operator*=(float right)
	{
		x *= right;
		y *= right;
	}

	void operator/=(Vector2 right)
	{
		x /= right.x;
		y /= right.y;
	}

	void operator/=(float right)
	{
		x /= right;
		y /= right;
	}

	Vector2 operator/(float other)
	{
		// ���ł�����Z�����炷
		// �Ӗ�������̂��͒m���I
		float factor = 1 / other;

		Vector2 result;
		result.x = x * factor;
		result.y = y * factor;
		return result;
	}

	Vector2 operator*(float other)
	{
		Vector2 result;
		result.x = x * other;
		result.y = y * other;
		return result;
	}

	Vector2 operator+(float other)
	{
		Vector2 result;
		result.x = x + other;
		result.y = y + other;
		return result;
	}

	Vector2 operator+(Vector2 other)
	{
		Vector2 result;
		result.x = x + other.x;
		result.y = y + other.y;
		return result;
	}

	Vector2 operator-(float other)
	{
		Vector2 result;
		result.x = x - other;
		result.y = y - other;
		return result;
	}

	Vector2 operator-(Vector2 other)
	{
		Vector2 result;
		result.x = x - other.x;
		result.y = y - other.y;
		return result;
	}

	// ����������I�[�o�[���[�h�H�c
	Vector2 operator-(Vector2 other) const
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
		// �����̐����������̑傫���Ŋ���(���)
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
};
