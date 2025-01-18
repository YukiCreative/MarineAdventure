#pragma once
#include "GameObject.h"
#include <string>
#include <unordered_map>
#include "Vector2.h"
#include <memory>

enum class DoorKind
{
	kTutoToMap1,
	Max,
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

// プロトタイプ宣言ってどこに書けばいいんだろう
class Image;
class Camera;
class CircleCollider;
class Player;

// マップの移動に使う
class Door : public GameObject
{
private:
	using  PathMap_t = std::unordered_map<MapKind, std::string>;
	static PathMap_t s_paths;

	// 仕方がないので特定の番号で行先と出現場所のセットを返す作りにする
	using  DoorMap_t = std::unordered_map<DoorKind, DoorStatus>;
	static DoorMap_t s_doors;

	// 自分はどのドアなのか
	DoorKind m_myKind;

	std::shared_ptr<Image> m_image;
	std::shared_ptr<CircleCollider> m_collider;
	Camera& m_camera;
	Player& m_player;

	bool CheckInDoor();
	void In();
public:
	/// <param name="mapPartsNum">Pratinumで設定する</param>
	Door(Player& player, Camera& camera, const Vector2& initPos, const int& mapPartsNum);

	void Update() override;
	void Draw() const override;
};

