#pragma once
#include "Vector2.h"

/// <summary>
/// �R���C�_�[���v�Z������ɏo�Ă��邢���ȏ����ЂƂ܂Ƃ߂ɂ��ĕԂ���������
/// </summary>
struct CollisionStatus
{
	// �������Ă��邩
	bool isCollide = false;
	// �߂荞��ł���Ƃ���̈�Ԓ�������
	// �������Ă���Α傫���͐��A�����łȂ���Ε�
	Vector2 overlap = Vector2::Zero();
	// �e���~�Ƃ��l�p�`�Ƃ��Ŋ撣���Ă��邵�Ȃ���o��
	// �P�ʃx�N�g��
	Vector2 normal = Vector2::Zero();
};