#include "MapDataStore.h"
#include <cassert>
#include "MapImageStore.h"
#include "ObjectKind.h"
#include <vector>
#include "MapConstants.h"
#include <Dxlib.h>

namespace
{
	constexpr int kLayerCount = 4;
	constexpr int kBitCount = 8;
	constexpr int kGraphInvisible = 0;
}

MapDataStore::MapDataStore(const std::string& path)
{
	m_mapData = std::make_unique<MapList_t>();
	LoadMapData(path);
}

void MapDataStore::LoadMapData(const std::string& path)
{
	int mapHandle = FileRead_open(path.c_str());
	// ���܂����o�C�g����ǂݍ��ށ@����͕ς��Ȃ�
	// !!!!assert�Ɋ֐������Ă͂����Ȃ�!!!!
	int err = FileRead_read(&m_fmfHeader, sizeof(m_fmfHeader), mapHandle);
	assert(err != -1 && "�t�@�C���̓ǂݍ��݂Ɏ��s���܂���");

	// FMF_���Ă̂�strID�ɂԂ�����ł�
	std::string strId;
	strId.resize(4);
	std::copy_n(m_fmfHeader.id, 4, strId.begin());
	// �킴�킴string�Ɏʂ��̂́A
	// �I�[�������ƁA
	// �G�f�B�^�̌x����ق点�邽�߂��Ɛ���
	assert(strId == "FMF_" && "�t�@�C���`�����s���ł�");
	assert(m_fmfHeader.bitCount == kBitCount && "�r�b�g�J�E���g��8�����Ή��ł��܂���");
	assert(m_fmfHeader.layerCount == kLayerCount && "���C���[��5�w�ɂȂ�܂���");

	// ��̃��C���[�̃o�C�g(=�`�b�v)�����擾
	int layerDataSize = m_fmfHeader.mapWidth * m_fmfHeader.mapHeight * (m_fmfHeader.bitCount / 8);
	
	// ���C���[��*�`�b�v���̗v�f����������
	m_mapData->clear();
	m_mapData->resize(m_fmfHeader.layerCount);
	for (auto& tempLayerData : *m_mapData)
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

MapChipData MapDataStore::GetMapData(const Vector2Int& mapPos) const
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
		result.decorationGraphHandle = -1;
		result.backGroundHandle = -1;
		// �����X�|�[�����Ȃ�
		result.objKind = ObjectKind::kEmpty;
		// �ꉞ����
		result.environment = MapConstants::kEnvironment::kWater;
	}
	else
	{
		const int chipIndex = mapPos.y * m_fmfHeader.mapWidth + mapPos.x;
		const int graphNum  = static_cast<int>((*m_mapData)[static_cast<int>(MapLayerAttribute::kMapChip)][chipIndex]);
		// ��
		result.environment           = static_cast<MapConstants::kEnvironment>((*m_mapData)[static_cast<int>(MapLayerAttribute::kEnvironment)][chipIndex]);
		// �o������I�u�W�F�N�g
		result.objKind               = static_cast<ObjectKind>((*m_mapData)[static_cast<int>(MapLayerAttribute::kObjects)][chipIndex]);
		// �w�i�摜
		result.decorationGraphHandle = imgStore.GetDecoGraph(static_cast<int>((*m_mapData)[static_cast<int>(MapLayerAttribute::kBackDecoration)][chipIndex]));
		result.backGroundHandle      = imgStore.GetBackGraph(static_cast<int>((*m_mapData)[static_cast<int>(MapLayerAttribute::kEnvironment)][chipIndex]));
		if (graphNum != kGraphInvisible)
		{
			result.graphHandle = imgStore.GetGraph(static_cast<int>((*m_mapData)[static_cast<int>(MapLayerAttribute::kMapChip)][chipIndex]));
		}
		else
		{
			// �摜�ԍ�kGraphInvisible�͓���
			// �����ȉ摜�n���h���ł��������A��ӂ̒l�ɂ��Ȃ���
			// �`�b�v���œ������ǂ����킩��Ȃ��Ƃ������׎d�l
			// bool�l�ł��������悤����
			result.graphHandle = -1;
		}
	}
	return result;
}

ObjectKind MapDataStore::GetObjKind(const Vector2Int& mapPos) const
{
	return static_cast<ObjectKind>((*m_mapData)[static_cast<int>(MapLayerAttribute::kObjects)][mapPos.x + mapPos.y * m_fmfHeader.chiphWidth]);
}

ObjectKind MapDataStore::GetObjKind(const int& index) const
{
	return static_cast<ObjectKind>((*m_mapData)[static_cast<int>(MapLayerAttribute::kObjects)][index]);
}
