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
	int m_clearTime;
	int m_startTime;
	int m_finishTime;
public:
	static Statistics& GetInstance();

	// それぞれのクラスから呼ぶ
	void GotCoin();
	void KilledEnemy();
	void BrokenBlock();

	void StartTimer();
	void StopTimer();

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
	// フレームを返す
	const int ClearTime()      const { return m_clearTime;      }
	const int ClearTimeMinutes() const;
	const int ClearTimeSeconds() const;

	const int GetCoinScoreMult();
	const int GetBlockScoreMult();
	const int GetEnemyScoreMult();
};

