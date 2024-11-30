#include "MapDataStore.h"
#include <cassert>

void MapDataStore::LoadMapData(std::string pass)
{
	int handle = FileRead_open(pass.c_str());
	// ���܂����o�C�g����ǂݍ��ށ@����͕ς��Ȃ�
	FileRead_read(&m_fmfHeader, sizeof(m_fmfHeader), handle);

	// FMF_���Ă̂�strID�ɂԂ�����ł�
	std::string strId;
	strId.resize(4);
	std::copy_n(m_fmfHeader.id, 4, strId.begin());
	// �킴�킴string�Ɏʂ��̂́A
	// �I�[�������ƁA
	// �G�f�B�^�̌x����ق点�邽�߂��Ɛ���
	if (strId != "FMF_") {
		assert(false && "�u�Ȃɂ��̃t�@�C���v���Č����Ă�B����");
	}

	// ��̃��C���[�̃o�C�g�����擾
	int layerDataSize = m_fmfHeader.mapWidth * m_fmfHeader.mapHeight * (m_fmfHeader.bitCount / 8);
	// ���シ�邱��
	// 1.�o�C�i���ǂݍ���
	// �@8�r�b�g��16�r�b�g���Ō^���g��������i�����₩�ȃR�s�y����Ȃ��A�s�[���j
	// �@MapData�\���̂ɂԂ�����
	// �@���C���[�������O��ŁA�Ԃ�����
	// �@��������X�}�[�g�ɌJ��Ԃ�����������
}

MapChipData MapDataStore::GetMapData(Vector2Int mapPos)
{
	return MapChipData();
}
