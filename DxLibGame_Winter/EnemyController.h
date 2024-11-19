#pragma once
#include <memory>
#include <list>

class Enemy;
class Player;
class Camera;

/// <summary>
/// シーンでこれをインスタンス化して
/// Enemyを管理してもらう
/// </summary>
class EnemyController
{
private:
	using EnemyList_t = std::list<std::shared_ptr<Enemy>>;
	EnemyList_t m_enemys;
	Player& m_playerRef;
	Camera& m_cameraRef;
public:
	EnemyController(Player& player, Camera& camera);

	void Update();
	void Draw();

	/// <summary>
	/// listに引数で渡された敵を追加します。
	/// mapchipとかに呼んでもらうイメージ
	/// </summary>
	/// <param name="enemy">敵</param>
	void SpawnEnemy(std::shared_ptr<Enemy> enemy);
};

