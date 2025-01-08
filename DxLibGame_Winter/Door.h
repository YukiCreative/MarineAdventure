#pragma once
#include "GameObject.h"
#include <string>
#include <unordered_map>

enum class MapKind
{
	kFish,
	kPipe,
	kMax
};

// �}�b�v�̈ړ��Ɏg��
class Door : public GameObject
{
private:
	using PathMap_t = std::unordered_map<MapKind, std::string>;
	static PathMap_t s_paths;

	std::string m_mapPath;

	void In();
public:
	/// <param name="mapPartsNum">Pratinum�Őݒ肷��</param>
	void SetNextMap(int mapPartsNum);

	void Update() override;
	void Draw() const override;
};

