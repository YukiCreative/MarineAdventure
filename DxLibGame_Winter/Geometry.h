#pragma once
#include "Vector2.h"

/// <summary>
/// �����ȎG�v�Z���W�߂Ēu����������
/// 11/28���ӁI�[�����Z���܂ފ֐�������̂ŁA�ꎟ�֐��͎g��Ȃ��ł��������B����ȏア����Ȃ���
/// </summary>
namespace Geometry
{
	/// <summary>
	/// ����
	/// �����v��
	/// </summary>
	struct Inf
	{

	};

	/// <summary>
	/// �ꎟ�֐��\����
	/// �X���A�ؕЂ�����
	/// </summary>
	struct LinearFunction
	{
		const float a = 0.1f;

	public:
		float slope = 0;
		float intercept = 0;
		
		/// <summary>
		/// ��̓_����A������ʂ�ꎟ�֐����v�Z
		/// </summary>
		LinearFunction(const Vector2& firstPos, const Vector2& secondPos)
		{
			Vector2 line = secondPos - firstPos;
			slope = Slope(line);
			intercept = Intercept(firstPos, slope);
		}

	private:
		/// <summary>
		/// ���݈ʒu�ƌX�����烏�[���h���W�̂����Ƃ̐ؕЂ����߂�
		/// </summary>
		float Intercept(const Vector2& pos, const float slope)
		{
			return pos.y - slope * pos.x;
		}
		/// <summary>
		/// �����̌X�����o���܂�
		/// �������H�����ɓ����̂͐��Ƃ��Ẵx�N�g������
		/// �ʒu�x�N�g��(���_����̃x�N�g��)�͓����ƌ��_����̌X�����o�邼
		/// </summary>
		float Slope(const Vector2& line)
		{
			// ���ꂘ��0�Ȃ牽���Ⴄ���̂�Ԃ��Ȃ��Ɓc
			return line.y / line.x;
		}
		/// <summary>
		/// �����ŗ^����ꂽ��̈ꎟ�������̌�_�̃��[���h���W��Ԃ��܂�
		/// ���s�Ȃ�Not a Vector()���Ԃ��Ă��܂��@�ԋp��ŁA���萔�ł�����������肢���܂�
		/// </summary>
		static Vector2 IntersectionOfLines(const LinearFunction& first, const LinearFunction& second)
		{
			Vector2 intersection;
			// �v�Z�ʐߖ�̂���
			const float slopeSub = first.slope - second.intercept;
			const float slopeSubFactor = 1 / slopeSub;
			// ���s�Ȃ�Ȃ񂩗ǂ��Ȃ��l��Ԃ�����
			if (slopeSub < 0.000001f) return NaV();
			intersection.x = second.intercept * slopeSubFactor - first.intercept * slopeSubFactor;
			intersection.y = second.slope * first.intercept * -slopeSubFactor - first.slope * second.intercept * -slopeSubFactor;
			return intersection;
		}
	};

	// �_�ƁA�����̍ŋߖT�_��Ԃ�
	Vector2 GetIntercept(Vector2 pos, Vector2 first, Vector2 second)
	{
		Vector2 startToEnd = second - first;
		// ���K��
		Vector2 startToEndN = startToEnd.GetNormalize();
		Vector2 startToPos = pos - first;
		float t = Vector2::InnerProduct(startToEndN, startToPos);
		// �x�N�g�������Ε����Ɍ������Ă�����
		if (t < 0)
		{
			return first;
		}
		// �x�N�g���������𒴂��Ă�����
		if (t * t > VSquareSize(startToEnd))
		{
			return second;
		}
		return first + startToEndN * t;
	}
}

// �ʖ���錾
namespace geo = Geometry;