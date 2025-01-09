#pragma once
#include "GameObject.h"
#include <string>
#include <unordered_map>
#include "Vector2.h"
#include <memory>

enum class DoorKind
{
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

// プロトタイプ宣言ってどこに書けばいいんだろう
class Image;

// マップの移動に使う
class Door : public GameObject
{
private:
	using PathMap_t = std::unordered_map<MapKind, std::string>;
	static PathMap_t s_paths;

	// 仕方がないので特定の番号で行先と出現場所のセットを返す作りにする
	using DoorMap_t = std::unordered_map<DoorKind, DoorStatus>;
	static DoorMap_t s_doors;

	// 自分はどのドアなのか
	DoorKind m_myKind;

	std::shared_ptr<Image> m_image;

	void In();
public:
	/// <param name="mapPartsNum">Pratinumで設定する</param>
	// Imageの初期化を行っているので、ドアの行き先を変える用途では使用できないよ
	void Init(int mapPartsNum);

	void Update() override;
	void Draw() const override;
};

