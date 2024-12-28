#pragma once
#include "Vector2.h"

/// <summary>
/// �����ȎG�v�Z���W�߂Ēu����������
/// </summary>
namespace Geometry
{
	// �_�ƁA�����̍ŋߖT�_��Ԃ�
	Vector2 GetSegmentIntercept(Vector2 pos, Vector2 first, Vector2 second)
	{
		Vector2 startToEnd = second - first;
		// ���K��
		Vector2 startToEndN = startToEnd.GetNormalize();
		Vector2 endToStartN = Vector2(first - second).GetNormalize();
		Vector2 startToPos = pos - first;
		Vector2 endToPos = pos - second;
		// �n�_����pos�̓��ς��݊p�Ȃ�A�ŋߖT�_�͎n�_
		if (startToEndN.Dot(startToPos) < 0)
		{
			return first;
		}
		// �I�_����pos���݊p�̎��A�ŋߖT�_�͏I�_
		else if (endToStartN.Dot(endToPos) < 0)
		{
			return second;
		}
		else
		{
			return first + startToEndN * startToEndN.Dot(startToPos);
		}
	}

	// �_�ƁA��_��ʂ钼���̍ŋߖT�_��Ԃ�
	Vector2 GetLineIntercept(Vector2 pos, Vector2 first, Vector2 second)
	{
		// ���K��
		Vector2 startToEndN = (second - first).GetNormalize();
		Vector2 startToPos = pos - first;
		return first + startToEndN * startToEndN.Dot(startToPos);
	}
}

// �ʖ���錾
namespace geo = Geometry;