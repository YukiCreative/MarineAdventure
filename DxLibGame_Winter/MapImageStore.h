#pragma once
#include <array>

namespace
{
	constexpr int kChipSize = 16;
	// �J��Ԃ��������Ăق�������萔�ŏ����܂�
	constexpr int kWidthChipNum = 16;
	constexpr int kHeightChipNum = 16;

	constexpr int kDecoImageWidth = 4;
	constexpr int kDecoImageHeight = 4;

	constexpr int kBackPartsWidth = 2;
	constexpr int kBackPartsHeight = 2;

	constexpr int kImageNum      = kWidthChipNum * kHeightChipNum;
	constexpr int kDecorationNum = kDecoImageWidth * kDecoImageHeight;
	constexpr int kBackGroundNum = kBackPartsWidth * kBackPartsHeight;
};

/// <summary>
/// �}�b�v�`�b�v�̉摜���ꊇ�œǂݍ���ŊǗ�����V���O���g���N���X
/// </summary>
class MapImageStore
{
private:
	MapImageStore();
	MapImageStore(const MapImageStore&) = delete;
	void operator=(const MapImageStore&) = delete;

	/// <summary>
	/// �}�b�v�`�b�v�̌�
	/// </summary>
	int m_sourceHandle;
	// �w�i�����p
	int m_decorationSourceHandle;
	int m_backGroundSourceHandle;

	std::array<int, kImageNum> m_imageArray;
	std::array<int, kDecorationNum> m_decoImageArray;
	std::array<int, kBackGroundNum> m_backImageArray;
public:

	/// <summary>
	/// ���x���Ȃ��݃C���X�^���X�擾
	/// </summary>
	/// <returns>�C���X�^���X�̎Q��</returns>
	static MapImageStore& GetInstance();

	/// <summary>
	/// MapID���󂯎���āA����ɊY������摜�̃n���h����Ԃ�
	/// </summary>
	/// <param name="id">�}�b�v�̒ʂ��ԍ����܂Ƃ߂��񋓑�</param>
	/// <returns>�Y������`�b�v�̉摜�̃n���h��</returns>
	int GetGraph(int id) const;
	int GetDecoGraph(int id) const;
	int GetBackGraph(int id) const;
};

