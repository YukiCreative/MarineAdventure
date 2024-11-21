#pragma once
#include <memory>
#include <vector>
#include <list>
#include <unordered_map>
#include "Vector2.h"

class Enemy;
class HarmFish;
class Player;
class Camera;

enum class EnemyKinds
{
	kHarmFish,
};

/// <summary>
/// シーンでこれをインスタンス化して
/// Enemyを管理してもらう
/// </summary>
class EnemyController
{
private:
	// Enemyに渡すため
	Player& m_playerRef;
	Camera& m_cameraRef;

	using EnemyList_t = std::list<std::shared_ptr<Enemy>>;
	EnemyList_t m_enemys;

	// Enemyの生成を列挙体から連想できるように関数を紐づける
	using EnemyFactory_t = std::shared_ptr<Enemy>(EnemyController::*)(Vector2 pos);
	std::shared_ptr<Enemy> CreateHarmFish(Vector2 spawnPos);
	std::unordered_map<EnemyKinds, EnemyFactory_t> m_factoryMap;
public:
	EnemyController(Player& player, Camera& camera);

	void Update();
	void Draw();

	/// <summary>
	/// 種類と位置を指定してくれればこちらで生成いたします
	/// </summary>
	void SpawnEnemy(EnemyKinds kind, Vector2 spawnPos);
	/// <summary>
	/// インスタンス渡してもいいよ
	/// </summary>
	void SpawnEnemy(std::shared_ptr<Enemy> enemyInstance);
	/// <summary>
	/// 配列にある敵を削除する
	/// とはいってもアドレスを知っているのは本人だけだけど
	/// </summary>
	/// <param name="deleteEnemy">削除するEnemyのスマポ</param>
	void DespawnEnemy(Enemy* deleteEnemy);
};

