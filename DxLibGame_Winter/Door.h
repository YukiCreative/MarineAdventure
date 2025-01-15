#pragma once
#include "GameObject.h"
#include <string>
#include <unordered_map>
#include "Vector2.h"
#include <memory>

enum class DoorKind
{
	// �G�Ƃ����܂Ƃ߂Ă���񋓑̂Ɣԍ������L���Ă���̂ł����Ȃ��Ă�
	kTutoToMap1 = 9,
};

enum class MapKind
{
	kFish,
	kPipe,
	kMax
};

struct DoorStatus
{
	const std::string path;
	const Vector2 appearPos;
};

// �v���g�^�C�v�錾���Ăǂ��ɏ����΂����񂾂낤
class Image;

// �}�b�v�̈ړ��Ɏg��
class Door : public GameObject
{
private:
	using PathMap_t = std::unordered_map<MapKind, std::string>;
	static PathMap_t s_paths;

	// �d�����Ȃ��̂œ���̔ԍ��ōs��Əo���ꏊ�̃Z�b�g��Ԃ����ɂ���
	using DoorMap_t = std::unordered_map<DoorKind, DoorStatus>;
	static DoorMap_t s_doors;

	// �����͂ǂ̃h�A�Ȃ̂�
	DoorKind m_myKind;

	std::shared_ptr<Image> m_image;

	void In();
public:
	/// <param name="mapPartsNum">Pratinum�Őݒ肷��</param>
	Door(const Vector2& initPos, const int& mapPartsNum);

	void Update() override;
	void Draw() const override;
};

