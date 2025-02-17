#pragma once

// ゲームでやったことをクリア時に表示したら楽しいのでは？
class Statistics
{
private:
	Statistics();
	Statistics(const Statistics&) = delete;
	void operator=(const Statistics&) = delete;

	int m_getCoinNum;
	int m_breakBlockNum;
	int m_killedEnemyNum;

	// 今のステージで稼いだ点数
	// 死んだときは戻す
	int m_tempGetCoinNum;
	int m_tempBreakBlockNum;
	int m_tempKilledEnemyNum;

	int m_clearTime;
public:
	static Statistics& GetInstance();

	// それぞれのクラスから呼ぶ
	void GotCoin();
	void KilledEnemy();
	void BrokenBlock();

	// ゲーム中に呼び出す
	void IncreaseTimer();

	// 今の統計からスコアだす
	int ScoreCoin() const;
	int ScoreEnemy() const;
	int ScoreBlock() const;
	int ScoreTime() const;
	int ScoreTotal() const;

	// ただメンバを返したい
	const int GetCoinNum()     const { return m_getCoinNum;     }
	const int BreakBlockNum()  const { return m_breakBlockNum;  }
	const int KilledEnemyNum() const { return m_killedEnemyNum; }
	const int GetCoinNowStageNum() const { return m_tempGetCoinNum; };
	// フレームを返す
	const int ClearTime()      const { return m_clearTime;      }
	const int ClearTimeMinutes() const;
	const int ClearTimeSeconds() const;

	const int GetCoinScoreMult();
	const int GetBlockScoreMult();
	const int GetEnemyScoreMult();

	// 今回のステージのスコアを保存する
	void SaveScore();
	// 今回のステージのスコアを破棄する
	void ResetNowStageScore();
	// スコアをリセット
	// タイトルに戻った時に流す
	void ResetAllScore();
};

