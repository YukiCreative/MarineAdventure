#pragma once
#include <array>

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
	/// �}�b�v�`�b�v�̃n���h�����W�߂�
	/// </summary>
	std::array<int, 168> m_imageArray = {};
	/// <summary>
	/// �}�b�v�`�b�v�̌�
	/// </summary>
	int m_sourceHandle;
public:
	/// <summary>
	/// �f�X�g���N�^
	/// �ǂ񂾉摜�̕Еt��
	/// </summary>
	~MapImageStore();

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
};

