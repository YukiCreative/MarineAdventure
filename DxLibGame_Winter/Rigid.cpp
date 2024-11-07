#include "Rigid.h"

Rigid::Rigid() :
	accel(),
	position(),
	weight(0.0f),
	airResistance(0.0f),
	waterResistance(0.0f),
	force()
{
}

void Rigid::Update()
{
	// ��R���l���Ĉړ�����
	// ma - kv���Ă��ƁH
	// �����x�����߂����̂ŁA
	// ��F�������Ă�����āA��������v�Z�����邱�ƂɂȂ邩��

	// �܂�F��m����Aa���o��
	// F = ma���Aa = F / m;
	// ����Z����̂��[
	accel = force / weight;
	// ���ɁA��R���o��
	// �������������ɂ���̂��A�n��ɂ���̂��Ŏg���萔��ς���

}
