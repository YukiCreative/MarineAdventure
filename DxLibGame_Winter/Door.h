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

// マップの移動に使う
class Door : public GameObject
{
private:
	using PathMap_t = std::unordered_map<MapKind, std::string>;
	static PathMap_t s_paths;

	std::string m_mapPath;

	void In();
public:
	/// <param name="mapPartsNum">Pratinumで設定する</param>
	void SetNextMap(int mapPartsNum);

	void Update() override;
	void Draw() const override;
};

