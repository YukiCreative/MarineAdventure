#pragma once
#include "MapConstants.h"
#include "ObjectKind.h"

// DataStore���番��
// �}�b�v�̂��낢����܂Ƃ߂�
// �O���ɓn���p
struct MapChipData
{
	int graphHandle;
	int backGraphHandle;
	// �G�A�M�~�b�N�ȂǃI�u�W�F�N�g�̗L���Ǝ�ނ��w�������񋓑�
	ObjectKind objKind;
	// �n��or����
	MapConstants::Environment environment;
};