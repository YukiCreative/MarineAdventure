#pragma once

/// <summary>
/// �G�⓮������u���b�N�ȂǁA
/// �I�u�W�F�N�g�S������ӂȒl�ŗ񋓂�������
/// </summary>
enum class ObjectKind
{
	kEmpty,
	kHarmFish,
	kBoss,
	// �ق��ɂ��ǉ��������I�u�W�F�N�g������̂ŁA�h�A�����ɒu���Ă���
	kDoor1 = 9, // ����(�S����)�ȊO�v�����Ȃ�����
	kDoor2,
	kDoor3,
	kDoor4,
	kDoor5,
	kDoor6,
	kDoor7,
	kDoor8,
};