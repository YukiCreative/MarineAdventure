#pragma once
#include "Scene.h"
#include <memory>
#include "Vector2.h"

class Player;
class MapSystem;
class Camera;
class HarmFish;
class ObjectsController;
class ImageObject;
class ScreenFade;

// �v���g�^�C�v�J�������ɂ���V�[��
class TestScene : public Scene
{
private:
	int m_frameCount;
	std::shared_ptr<MapSystem> m_map;
	std::shared_ptr<Player> m_player;
	std::shared_ptr<ObjectsController> m_objectCont;
	std::shared_ptr<ImageObject> m_backGround;

	// �}�b�v�؂�ւ������֘A
	std::string m_nextMapPath;
	Vector2 m_playerTransportPos;
	bool m_isMapChanging;

	void ChangeMap(const std::string& path);
	void ChangeMap(const std::string& path, const Vector2& playerTransferPos);

	// �}�b�v���ς��܂ő҂��
	void MapChangeUpdate();

protected:
	void NormalUpdate() override;

public:
	TestScene();
	~TestScene();

	void GameClear();
	void GameOver();

	void ChangeMapWithFadeOut(const std::string& path, const Vector2& playerTransferPos);

	void Entry() override;

	void Draw() const override;
};

