#pragma once

// �Q�[���ł�������Ƃ��N���A���ɕ\��������y�����̂ł́H
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

	// ���ꂼ��̃N���X����Ă�
	void GotCoin();
	void KilledEnemy();
	void BrokenBlock();

	void StartTimer();
	void StopTimer();

	// ���̓��v����X�R�A����
	int ScoreCoin() const;
	int ScoreEnemy() const;
	int ScoreBlock() const;
	int ScoreTime() const;
	int ScoreTotal() const;

	// ���������o��Ԃ�����
	const int GetCoinNum()     const { return m_getCoinNum;     }
	const int BreakBlockNum()  const { return m_breakBlockNum;  }
	const int KilledEnemyNum() const { return m_killedEnemyNum; }
	// �t���[����Ԃ�
	const int ClearTime()      const { return m_clearTime;      }
	const int ClearTimeMinutes() const;
	const int ClearTimeSeconds() const;

	const int GetCoinScoreMult();
	const int GetBlockScoreMult();
	const int GetEnemyScoreMult();
};

