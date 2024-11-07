#pragma once
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

	void operator/=(Vector2 right)
	{
		x /= right.x;
		y /= right.y;
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
};
