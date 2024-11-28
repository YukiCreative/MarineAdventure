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

	// float����̕ϊ��R���X�g���N�^
	// float�̉��Z�q�I�[�o�[���[�h���ȗ��ł���
	Vector2(float value) : x(value), y(value)
	{
	}

	// DxLib��VECTOR�Ƃ̕ϊ��֐�
	// ��ނȂ�DxLib���C���N���[�h
	operator VECTOR() const
	{
		return VGet(x, y, 0.0f);
	}

	// ���ꂪ�����Vector2���ǂ���������
	// �h���N���X��NaV�͕K��false��Ԃ�
	virtual bool IsValid()
	{
		return true;
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

	void operator*=(const float& right)
	{
		x *= right;
		y *= right;
	}

	Vector2 operator/(const float& other)
	{
		// ���ł�����Z�����炷
		// �Ӗ�������̂��͒m���I
		float factor = 1 / other;

		Vector2 result;
		result.x = x * factor;
		result.y = y * factor;
		return result;
	}

	Vector2 operator*(const float& other)
	{
		Vector2 result;
		result.x = x * other;
		result.y = y * other;
		return result;
	}

	Vector2 operator+(const Vector2& other)
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

	Vector2 operator-(const Vector2& other)
	{
		Vector2 result;
		result.x = x - other.x;
		result.y = y - other.y;
		return result;
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

	// ����
	static float InnerProduct(const Vector2& first, const Vector2& second)
	{
		return first.x * second.x + first.y * second.y;
	}
};

/// <summary>
/// Not a Vector
/// �Ⴂ�́A�L�����ǂ����q�˂�ꂽ��K��false��Ԃ�����
/// �v�Z�ŁA�Ԃ�Vector�����Ȃ��ɂȂ����Ƃ��Ƃ��ɓn��
/// </summary>
struct NaV : public Vector2
{
	bool IsValid() override
	{
		return false;
	}
};