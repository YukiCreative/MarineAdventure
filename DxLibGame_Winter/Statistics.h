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
	int m_playTime;

	// �^�C���X�R�A���v�Z
	int ScoreTime() const;
public:
	static Statistics& GetInstance();

	// ���ꂼ��̃N���X����Ă�
	void GotCoin();
	void KilledEnemy();
	void BrokenBlock();

	// ���̓��v����X�R�A����
	int Score() const;
};

