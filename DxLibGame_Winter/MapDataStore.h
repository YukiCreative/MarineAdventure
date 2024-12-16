#pragma once
#include "Vector2.h"
#include "string"
#include <vector>
#include <memory>
#include "ObjectKind.h"

// �}�b�v�̂��낢����܂Ƃ߂�
// �����ł͎g��Ȃ�����
struct MapChipData
{
	int graphHandle;
	// �G�A�M�~�b�N�ȂǃI�u�W�F�N�g�̗L���Ǝ�ނ��w�������񋓑�
	ObjectKind objKind;
};

/// <summary>
/// �O���t�@�C������}�b�v�̃f�[�^��ǂݍ���ŁA
/// �����Ă��Ă����N���X
/// Scene�Ɏ������悤����
/// </summary>
class MapDataStore
{
private:
	//FMF�w�b�_�[(Platinum�̃h�L�������g�ɏ����Ă���)
	struct Header
	{
		int8_t id[4];			//���ʎq(FMF_)		1*4�o�C�g
		uint32_t size;			//�f�[�^�T�C�Y�@		4�o�C�g
		uint32_t mapWidth;		//�}�b�v�̕�			4�o�C�g
		uint32_t mapHeight;		//�}�b�v�̍����@		4�o�C�g
		uint8_t chiphWidth;		//�`�b�v(�Z�����)�̕�				1�o�C�g
		uint8_t chpHeight;		//�`�b�v(�Z�����)�̍���				1�o�C�g
		uint8_t layerCount;		//���C���[�̐�						1�o�C�g
		uint8_t bitCount;		//�P�Z��������̃r�b�g��(��8�Ńo�C�g��)	1�o�C�g
	};//20�o�C�g

	// ���̃}�b�v�f�[�^�̃w�b�_�����L�����Ă���
	Header m_fmfHeader;

	// �Ȃ���
	// �߂�ǂ�����X�^�b�N�ɓ���Ă����H
	using MapList_t = std::vector<std::vector<uint8_t>>;
	MapList_t m_mapData;
public:
	MapDataStore(std::string pass);

	// �����ʂ�
	// �Â��}�b�v�f�[�^�̓X�}�|�Ŕj�������
	void LoadMapData(std::string pass);

	/// <summary>
	/// �}�b�v���W���炨�ړ��Ẵ}�b�v�`�b�v�̃f�[�^��Ԃ�
	/// </summary>
	/// <param name="id"></param>
	MapChipData GetMapData(Vector2Int mapPos);

	Vector2Int GetMapSize() const { return Vector2Int(m_fmfHeader.mapWidth, m_fmfHeader.mapHeight); }
};

