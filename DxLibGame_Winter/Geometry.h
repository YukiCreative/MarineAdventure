#pragma once
#include "Vector2.h"

/// <summary>
/// �����ȎG�v�Z���W�߂Ēu����������
/// </summary>
namespace Geometry
{
	/// <summary>
	/// �ꎟ�֐��\����
	/// �X���A�ؕЂ�����
	/// </summary>
	struct LinearFunction
	{
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
			if (slopeSub == 0.0f) return NaV();
			intersection.x = second.intercept * slopeSubFactor - first.intercept * slopeSubFactor;
			intersection.y = second.slope * first.intercept * -slopeSubFactor - first.slope * second.intercept * -slopeSubFactor;
			return intersection;
		}
	};
}

// �ʖ���錾
namespace geo = Geometry;