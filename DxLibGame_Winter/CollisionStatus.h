#pragma once
#include "Vector2.h"

/// <summary>
/// �R���C�_�[���v�Z������ɏo�Ă��邢���ȏ����ЂƂ܂Ƃ߂ɂ��ĕԂ���������
/// </summary>
struct CollisionStatus
{
	// �������Ă��邩
	bool isCollide = false;
	// ���������ʂɐ����ɁA�ǂꂭ�炢�̌����A�傫���ł߂荞��ł��邩���o���Ă���܂�
	Vector2 overlap = Vector2::Zero();
};