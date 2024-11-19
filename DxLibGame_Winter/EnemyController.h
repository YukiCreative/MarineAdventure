#pragma once
#include <memory>
#include <vector>

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
	using EnemyList_t = std::vector<std::shared_ptr<Enemy>>;
	EnemyList_t m_enemys;
public:

	void Update();
	void Draw();

	/// <summary>
	/// listに引数で渡された敵を追加します。
	/// mapchipとかに呼んでもらうイメージ
	/// </summary>
	/// <param name="enemy">敵</param>
	void SpawnEnemy(std::shared_ptr<Enemy> enemy);
	/// <summary>
	/// 配列にある敵を削除する
	/// とはいってもアドレスを知っているのは本人だけだけど
	/// </summary>
	/// <param name="deleteEnemy">削除するEnemyのスマポ</param>
	void DespawnEnemy(Enemy& deleteEnemy);
};

