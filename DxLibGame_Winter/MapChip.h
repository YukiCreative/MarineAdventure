#pragma once
#include "Vector2.h"
#include <memory>
#include "GameObject.h"
#include "ObjectKind.h"

class BoxCollider;
class Camera;
class ObjectsController;
class MapSystem;
class Player;
class Image;
struct MapChipData;

/// <summary>
/// �}�b�v�`�b�v����̉摜��S������
/// MapSystem��������Œ�z��Ŏ���
/// </summary>
class kMapChip : public GameObject
{
private:
	// ���������}�b�v�̂ǂ̃`�b�v��S�����Ă��邩���L��
	Vector2Int m_mapPos;
	// �������L��
	Vector2 m_movePos;
	// �摜
	std::shared_ptr<Image> m_chipImage;
	std::shared_ptr<Image> m_backImage;
	// �����蔻��
	std::shared_ptr<BoxCollider> m_collider;
	// �J��������
	Camera& m_camera;
	// �G���Ăяo��
	ObjectsController& m_objectsController;
	MapSystem& m_system;
	/// <summary>
	/// ��������ʊO�ɏo�Ă��邩���`�F�b�N���āA
	/// �����Ȃ�Έ�����邩�̂悤�ɍ��W���ړ�������
	/// </summary>
	/// <returns>true:��ʊO�����ʂ��� false:��ʓ��ł���</returns>
	bool LoopScreen();
	bool CheckLoopUpAndLeft();
	bool CheckLoopDownAndRight();

	/// <summary>
	/// ���݂̃}�b�v�̃f�[�^���Q�Ƃ��āA
	/// �����̎��O���t�f�[�^�����߂�
	/// </summary>
	void ResetMapData();
public:
	// ���������񂲂�
	// ���낢���点��������
	kMapChip(Camera& camera, ObjectsController& cont, const Vector2 initPos, const Vector2Int initMapPos, MapSystem& system);

	/// <summary>
	/// �X�V����
	/// ��ʊO�ɏo���������Ė߂��Ă���
	/// �V�����摜���擾����
	/// </summary>
	void Update() override;

	/// <summary>
	/// �����`��
	/// </summary>
	void Draw() const override;

	/// <summary>
	/// MapSystem����w�����󂯂�
	/// </summary>
	/// <param name="">���ݒn����ǂꂾ����������</param>
	void Move(Vector2 moveValue) { m_movePos += moveValue; }

	/// <summary>
	/// ���W�Ԃ�
	/// </summary>
	/// <returns>���W</returns>
	Vector2 GetPos() const { return m_pos; }

	/// <summary>
	/// �Ԃ�����
	/// �Ȃ񂩎󂯓n�����ʓ|�ɂȂ��Ă�����
	/// </summary>
	/// <returns>�}�b�v�`�b�v�̃R���C�_�[</returns>
	BoxCollider& GetCollider() const { return *m_collider; }

	bool CanCollide() const;
	MapChipData GetMapChipData() const;
	void ChangeGraph_Debug();
};

