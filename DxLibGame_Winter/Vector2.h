#pragma once
#include <cmath>
#include <limits>
#include <DxLib.h>
#include "Calculation.h"
// ���̃X�N���v�g�ɂ͓��ɁA����include���Ȃ����ƁI

/// <summary>
/// �w�b�_�I�����[�̍\����
/// </summary>
struct Vector2
{
protected:
	// NaV�p
	Vector2(bool valid) : x(0), y(0), isValid(valid) {}

public:
	float x, y;
	bool isValid;

	Vector2() : x(0), y(0), isValid(true)
	{
	}

	Vector2(const float& _x, const float& _y) : x(_x), y(_y), isValid(true)
	{
	}

	Vector2(const int& _x, const int& _y) : x(static_cast<float>(_x)), y(static_cast<float>(_y)), isValid(true)
	{
	}

	// float����̕ϊ��R���X�g���N�^
	// float�̉��Z�q�I�[�o�[���[�h���ȗ��ł���
	Vector2(const float& value) : x(value), y(value), isValid(true)
	{
	}

	// DxLib��VECTOR�Ƃ̕ϊ��֐�
	// cpp�Ŏ����ł��Ȃ�����
	operator VECTOR() const
	{
		return VGet(x, y, 0.0f);
	}

	bool operator==(Vector2& right) const
	{
		// X��Y�ǂ���������l�Ȃ�true��Ԃ�
		return (x == right.x && y == right.y);
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

	Vector2 operator*(const float& other) const
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
	virtual float SqrMagnitude() const
	{
		return x * x + y * y;
	}

	/// <summary>
	///  �傫���Ԃ�
	/// </summary>
	/// <returns>�傫��</returns>
	float Magnitude() const
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
	Vector2 GetNormalize() const
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

	/// <summary>
	/// �⊮������̃x�N�g����Ԃ��̂ł͂Ȃ��A
	/// start�ɑ�������⊮�ɂȂ�x�N�g����Ԃ�
	/// </summary>
	static Vector2 LerpValue(const Vector2& start, const Vector2& end, const float& rate)
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
		return (end - start) * clampRate;
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
	float Dot(const Vector2& second) const
	{
		return x * second.x + y * second.y;
	}

	// X���������n���Ƃ����p�x
	// Y�����������Ȃ̂Ŏ��v��肪���̊p�x�ɂȂ�
	// �[���x�N�g����0�x�ɂȂ�͎̂d�l
	float Angle() const
	{
		float rad = atan2(y, x);
		if (rad < 0)
		{
			rad += Calculation::kPi * 2;
		}
		return rad * Calculation::kRadToDeg;
	}

	// �����ɓ����ꂽ�x�N�g���Ƃ̂Ȃ��p���o��(�x��)
	// ���v��肪�v���X�A�����v��肪�}�C�i�X
	float RerativeAngle(const Vector2& other) const
	{
		float myDeg = this->Angle();
		float otherDeg = other.Angle();
		return myDeg - otherDeg;
	}

	// ���M�����v����deg�x�񂵂��x�N�g����Ԃ�
	// ����͎O�p�֐����g�����A������s�񂩃N�I�[�^�j�I�����g������
	// sqrt���g���Ă���̂ŏd������
	Vector2 RotatedVec(const float& deg) const
	{
		Vector2 rotatedVec;
		float myAngle = Angle();
		float mySize = Magnitude();
		rotatedVec.x = mySize * cosf((myAngle + deg) * Calculation::kDegToRad);
		rotatedVec.y = mySize * sinf((myAngle + deg) * Calculation::kDegToRad);
		return rotatedVec;
	}
};

/// <summary>
/// Not a Vector
/// �Ⴂ�́A�L�����ǂ����q�˂�ꂽ��K��false��Ԃ�����
/// �v�Z�ŁA�Ԃ�Vector�����Ȃ��ɂȂ����Ƃ��Ƃ��ɓn��
/// </summary>
struct NaV : public Vector2
{
	NaV() : Vector2(false){}

	// �_�E���L���X�g�p
	explicit NaV(Vector2) : Vector2(false) {};

	float SqrMagnitude() const override
	{
		return std::numeric_limits<float>::quiet_NaN();
	}
};

/// <summary>
/// int�^�Ƃ��Ďg���f�[�^�A�ł���ꏏ�ɂ��Ĉ��������c�I
/// ����Ȃ��Ȃ���
/// ��{�I�ȎZ�p���Z�q�̂ݑΉ�
/// �����ĕ��������_�ɂ͂Ȃ炸�A�؂�̂Ă���̂Œ���
/// </summary>
struct Vector2Int
{
	int x;
	int y;

	Vector2Int() : x(0), y(0) {}

	Vector2Int(const int& _x, const int& _y) : x(_x), y(_y) {}

	Vector2Int(const int& value) : x(value), y(value) {}

	// Vector2�ւ̕ϊ��֐�
	operator Vector2()
	{
		return Vector2(static_cast<float>(x), static_cast<float>(y));
	}

	operator const Vector2() const
	{
		return Vector2(static_cast<float>(x), static_cast<float>(y));
	}

	void operator+=(const Vector2Int& right)
	{
		x += right.x;
		y += right.y;
	}

	void operator-=(const Vector2Int& right)
	{
		x -= right.x;
		y -= right.y;
	}

	void operator*=(const int& right)
	{
		x *= right;
		y *= right;
	}

	Vector2Int operator*(const int& right)
	{
		return Vector2Int(x * right, y * right);
	}

	void operator/=(int right)
	{
		x /= right;
		y /= right;
	}

	Vector2Int operator/(const int& right)
	{
		return Vector2Int(x / right, y / right);
	}
};