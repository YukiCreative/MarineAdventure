#include "Statistics.h"
#include "Time.h"
#include "game.h"

namespace
{
    // åWêîÇÃñΩñºÇ¡ÇƒÇ«ÇÍÇ™Ç¢Ç¢ÇÒÇæÇÎÇ§
    constexpr int kCoinScoreMult = 300;
    constexpr int kEnemyScoreMult = 500;
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
    m_clearTime(0),
    m_startTime(0),
    m_finishTime(0)
{
}

int Statistics::ScoreTotal() const
{
    int coinScore = m_getCoinNum * kCoinScoreMult;
    int blockScore = m_breakBlockNum * kBlockScoreMult;
    int enemyScore = m_killedEnemyNum * kEnemyScoreMult;

    int timeScore = ScoreTime();

    return (coinScore + blockScore + enemyScore) * timeScore;
}

const int Statistics::ClearTimeMinutes() const
{
    return m_clearTime / Game::kFrameRate / 60;
}

const int Statistics::ClearTimeSeconds() const
{
    return m_clearTime / Game::kFrameRate % 60;
}

const int Statistics::GetCoinScoreMult()
{
    return kCoinScoreMult;
}

const int Statistics::GetBlockScoreMult()
{
    return kBlockScoreMult;
}

const int Statistics::GetEnemyScoreMult()
{
    return kEnemyScoreMult;
}

int Statistics::ScoreTime() const
{
    if (m_clearTime <= kFastTime) return kFastTimeScoreMult;
    if (m_clearTime <= kMiddleTime) return kMiddleTimeScoreMult;
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
    m_clearTime = m_finishTime - m_startTime;
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
