#include "Statistics.h"
#include "Time.h"
#include "game.h"

namespace
{
    // åWêîÇÃñΩñºÇ¡ÇƒÇ«ÇÍÇ™Ç¢Ç¢ÇÒÇæÇÎÇ§
    constexpr int kCoinScoreMult = 500;
    constexpr int kEnemyScoreMult = 300;
    constexpr int kBlockScoreMult = 200;
    constexpr int kFastTimeScoreMult = 3;
    constexpr int kMiddleTimeScoreMult = 2;
    constexpr int kLateTimeScoreMult = 1;
    constexpr int kFastTime = 180 * Game::kFrameRate;
    constexpr int kMiddleTime = 240 * Game::kFrameRate;
    constexpr int kLateTime = 300 * Game::kFrameRate;
}

Statistics::Statistics() :
    m_breakBlockNum(0),
    m_getCoinNum(0),
    m_killedEnemyNum(0),
    m_playTime(0),
    m_startTime(0),
    m_finishTime(0)
{
}

int Statistics::Score() const
{
    int coinScore = m_getCoinNum * kCoinScoreMult;
    int blockScore = m_breakBlockNum * kBlockScoreMult;
    int enemyScore = m_killedEnemyNum * kEnemyScoreMult;

    int timeScore = ScoreTime();

    return (coinScore + blockScore + enemyScore) * timeScore;
}

int Statistics::ScoreTime() const
{
    if (m_playTime <= kFastTime) return kFastTimeScoreMult;
    if (m_playTime <= kMiddleTime) return kMiddleTimeScoreMult;
    return kLateTimeScoreMult;
}

Statistics& Statistics::GetInstance()
{
    static Statistics instance;
    return instance;
}

void Statistics::GotCoin()
{
    ++m_getCoinNum;
}

void Statistics::KilledEnemy()
{
    ++m_killedEnemyNum;
}

void Statistics::BrokenBlock()
{
    ++m_breakBlockNum;
}

void Statistics::StartTimer()
{
    m_startTime = Time::GetInstance().FrameCount();
}

void Statistics::StopTimer()
{
    m_finishTime = Time::GetInstance().FrameCount();
    m_playTime = m_finishTime - m_startTime;
}

int Statistics::ScoreCoin() const
{
    return m_getCoinNum * kCoinScoreMult;
}

int Statistics::ScoreEnemy() const
{
    return m_killedEnemyNum* kEnemyScoreMult;
}

int Statistics::ScoreBlock() const
{
    return m_breakBlockNum * kBlockScoreMult;
}
