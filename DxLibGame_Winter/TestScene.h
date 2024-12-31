#pragma once
#include "Scene.h"
#include <memory>

class Player;
class MapSystem;
class Camera;
class HarmFish;
class ObjectsController;
class MapDataStore;
class BackGround;
class ScreenFade;

// プロトタイプ開発を共にするシーン
class TestScene : public Scene
{
private:
	int m_frameCount;
	std::shared_ptr<MapSystem> m_map;
	std::shared_ptr<Player> m_player;
	std::shared_ptr<Camera> m_camera;
	std::shared_ptr<ObjectsController> m_objectCont;
	std::shared_ptr<MapDataStore> m_mapDataStore;
	std::shared_ptr<BackGround> m_backGround;
public:
	TestScene();
	~TestScene();

	void Entry() override;
	void NormalUpdate() override;
	void Draw() const override;
};

