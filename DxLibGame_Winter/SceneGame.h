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
class HitPoints;
class CoinUI;
class TimeUI;

enum class Stages
{
	kStage1,
	kStage2,
	kStage3
};

class SceneGame : public Scene
{
private:
	// 今のステージ
	// コンティニューで使う
	static Stages s_nowStage;

	int m_frameCount;
	std::shared_ptr<MapSystem> m_map;
	std::shared_ptr<Player> m_player;
	std::shared_ptr<ObjectsController> m_objectCont;
	std::shared_ptr<HitPoints> m_hpUI;
	std::shared_ptr<CoinUI> m_coinUI;
	std::shared_ptr<TimeUI> m_timeUI;

	// マップ切り替え処理関連
	std::string m_nextMapPath;
	Vector2 m_playerTransportPos;
	bool m_isMapChanging;
	int m_stopFrame;

	void ChangeMap(const std::string& path);
	void ChangeMap(const std::string& path, const Vector2& playerTransferPos);

	// マップが変わるまで待つ状態
	void MapChangeUpdate();
	void HitStopUpdate();
protected:
	void NormalUpdate() override;

public:
	SceneGame();
	~SceneGame();

	void Init() override;
	void GameClear();
	void GameOver();

	void ChangeMapWithFadeOut(const Stages stage, const std::string& path, const Vector2& playerTransferPos);

	void Entry() override;

	void Draw() const override;

	// ObjectsControllerをそのまま返してしまう
	// 適当にSceneControllerのCurrentSceneからダウンキャストしてちょ
	std::weak_ptr<ObjectsController> GetObjectsController() { return m_objectCont; }

	void HitStop(const int frame);
	// コードが汚くなってきたぜ
	MapSystem& GetMap() { return *m_map; }
	static void ResetStageProgress();
};

