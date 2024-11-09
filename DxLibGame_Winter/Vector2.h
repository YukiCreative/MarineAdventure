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

	/// <summary>
	/// �傫���̓���Ԃ�
	/// </summary>
	/// <returns>�x�N�g���̑傫���̓��</returns>
	float SqrMagnitude()
	{
		return x * x + y * y;
	}

	/// <summary>
	/// ������P�ʃx�N�g���ɂ���
	/// </summary>
	void Normalize()
	{
		float mag = SqrMagnitude();
		// �傫����0�Ȃ�return
		if (!mag) return;
		// �����̐����������̑傫���Ŋ���(���)
		x = (x * x) / mag;
		y = (y * y) / mag;
	}

	/// <summary>
	/// �P�ʃx�N�g���ɂ����R�s�[��Ԃ�
	/// </summary>
	/// <returns>�P�ʃx�N�g��(�R�s�[)</returns>
	Vector2 GetNormalize()
	{
		Vector2 result;
		float mag = SqrMagnitude();
		if (!mag) return result;
		result.x = (x * x) / mag;
		result.y = (y * y) / mag;
		return result;
	}
};
