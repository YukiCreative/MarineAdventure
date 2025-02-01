#pragma once
#include "Vector2.h"
#include <memory>
#include "GameObject.h"
#include "ObjectKind.h"
#include "MapChipData.h"

class BoxCollider;
class Camera;
class ObjectsController;
class MapSystem;
class Player;
class Image;
class Animation;

/// <summary>
/// �}�b�v�`�b�v����̉摜��S������
/// MapSystem��������Œ�z��Ŏ���
/// </summary>
class MapChip : public GameObject
{
private:
	// ���������}�b�v�̂ǂ̃`�b�v��S�����Ă��邩���L��
	Vector2Int m_mapPos;
	// �������L��
	Vector2 m_movePos;
	// �摜
	std::shared_ptr<Image> m_chipImage;
	std::shared_ptr<Image> m_backDecorationImage;
	std::shared_ptr<Image> m_backGroundImage;
	// �����������̎�������ԏ�ɏd�˂ĕ`�悳���
	std::shared_ptr<Animation> m_marineAnimation;
	// �����蔻��
	std::shared_ptr<BoxCollider> m_collider;
	// �J��������
	Camera& m_camera;
	MapSystem& m_system;
	std::weak_ptr<ObjectsController> m_objCont;
	MapChipData m_mapChipData;
	/// <summary>
	/// ��������ʊO�ɏo�Ă��邩���`�F�b�N���āA
	/// �����Ȃ�Έ�����邩�̂悤�ɍ��W���ړ�������
	/// </summary>
	/// <returns>true:��ʊO�����ʂ��� false:��ʓ��ł���</returns>
	bool LoopScreen();
	bool CheckLoopUpAndLeft();
	bool CheckLoopDownAndRight();
public:
	// ���������񂲂�
	// ���낢���点��������
	MapChip(Camera& camera, const Vector2 initPos, const Vector2Int initMapPos, MapSystem& system);

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
	// ���̂Ƃ���w�i(��)�݂̂�`��
	void BackDraw() const;

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
	/// ���݂̃}�b�v�̃f�[�^���Q�Ƃ��āA
	/// �����̎��O���t�f�[�^�����߂�
	/// </summary>
	void ResetMapData();

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

