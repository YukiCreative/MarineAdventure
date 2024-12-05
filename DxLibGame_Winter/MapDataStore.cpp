#include "MapDataStore.h"
#include <cassert>
#include "MapImageStore.h"
#include "ObjectKind.h"
#include <vector>
#include "MapConstants.h"

namespace
{
	constexpr int kLayerCount = 2;
	constexpr int kBitCount = 8;
	constexpr int kGraphInvisible = 159;
}

MapDataStore::MapDataStore(std::string pass)
{
	LoadMapData(pass);
}

void MapDataStore::LoadMapData(std::string pass)
{
	int mapHandle = FileRead_open(pass.c_str());
	// ���܂����o�C�g����ǂݍ��ށ@����͕ς��Ȃ�
	FileRead_read(&m_fmfHeader, sizeof(m_fmfHeader), mapHandle);
	assert(m_fmfHeader.bitCount == kBitCount && "�r�b�g�J�E���g��8�����Ή��ł��܂���");
	assert(m_fmfHeader.layerCount == kLayerCount && "���C���[�͓�w�ł������܂�");

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

	// ��̃��C���[�̃o�C�g(=�`�b�v)�����擾
	int layerDataSize = m_fmfHeader.mapWidth * m_fmfHeader.mapHeight * (m_fmfHeader.bitCount / 8);
	
	// ���C���[��*�`�b�v���̗v�f����������
	m_mapData.resize(m_fmfHeader.layerCount);
	for (auto& tempLayerData : m_mapData)
	{
		// �v�f�����m�ۂ��[��
		tempLayerData.resize(layerDataSize);
		// �����Ŋe���C���[�Ƀf�[�^���Ԃ�����
		// FileRead_read�͑�������ǂݍ��ނ񂾂Ǝv��
		int result = FileRead_read(tempLayerData.data(), layerDataSize, mapHandle);
		assert(result != -1 && "�t�@�C���ǂݍ��ݒ��ɕs�");
	}
	// �����Ńt�@�C���̖����͏I���
	FileRead_close(mapHandle);
}

MapChipData MapDataStore::GetMapData(Vector2Int mapPos)
{
	// �����Ńn���h����񋓑̂ȂǁA�g����`�ɂ��Ă��܂�
	MapChipData result;
	MapImageStore& imgStore = MapImageStore::GetInstance();
	// �}�b�v�̑��݂���͈͊O�Ȃ��
	if (mapPos.x < 0 ||
		mapPos.y < 0 ||
		mapPos.x >= static_cast<int>(m_fmfHeader.mapWidth) ||
		mapPos.y >= static_cast<int>(m_fmfHeader.mapHeight))
	{
		// �����摜�����Ȃ�->����
		result.graphHandle = -1;
		// �����X�|�[�����Ȃ�
		result.objKind = ObjectKind::kEmpty;
	}
	else
	{
		const int chipIndex = mapPos.y * m_fmfHeader.mapWidth + mapPos.x;
		const int graphNum = static_cast<int>((m_mapData)[0][chipIndex]);
		if (graphNum != kGraphInvisible)
		{
			result.graphHandle = imgStore.GetGraph(static_cast<int>((m_mapData)[0][chipIndex]));
		}
		else
		{
			// �摜�ԍ�0�͓���
			// �����ȉ摜�n���h���ł��������A��ӂ̒l�ɂ��Ȃ���
			// �`�b�v���œ������ǂ����킩��Ȃ��Ƃ������׎d�l
			result.graphHandle = -1;
		}
		result.objKind = static_cast<ObjectKind>((m_mapData)[1][chipIndex]);
	}
	return result;
}
