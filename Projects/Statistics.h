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

	// ���̃X�e�[�W�ŉ҂����_��
	// ���񂾂Ƃ��͖߂�
	int m_tempGetCoinNum;
	int m_tempBreakBlockNum;
	int m_tempKilledEnemyNum;

	int m_clearTime;
public:
	static Statistics& GetInstance();

	// ���ꂼ��̃N���X����Ă�
	void GotCoin();
	void KilledEnemy();
	void BrokenBlock();

	// �Q�[�����ɌĂяo��
	void IncreaseTimer();

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
	const int GetCoinNowStageNum() const { return m_tempGetCoinNum; };
	// �t���[����Ԃ�
	const int ClearTime()      const { return m_clearTime;      }
	const int ClearTimeMinutes() const;
	const int ClearTimeSeconds() const;

	const int GetCoinScoreMult();
	const int GetBlockScoreMult();
	const int GetEnemyScoreMult();

	// ����̃X�e�[�W�̃X�R�A��ۑ�����
	void SaveScore();
	// ����̃X�e�[�W�̃X�R�A��j������
	void ResetNowStageScore();
	// �X�R�A�����Z�b�g
	// �^�C�g���ɖ߂������ɗ���
	void ResetAllScore();
};

