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
	int m_playTime;
	int m_startTime;
	int m_finishTime;

	// タイムスコアを計算
	int ScoreTime() const;
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
	int Score() const;
};

