#include "GameSettings.h"

namespace
{
    constexpr int EASY_FALL_INTERVAL_MS = 500;
    constexpr int NORMAL_FALL_INTERVAL_MS = 300;
    constexpr int HARD_FALL_INTERVAL_MS = 180;
}

GameSettings::GameSettings()
    : difficulty(GameDifficulty::Normal)
{
}

GameDifficulty GameSettings::Difficulty() const
{
    return difficulty;
}

int GameSettings::FallIntervalMs() const
{
    switch (difficulty)
    {
    case GameDifficulty::Easy:
        return EASY_FALL_INTERVAL_MS;
    case GameDifficulty::Normal:
        return NORMAL_FALL_INTERVAL_MS;
    case GameDifficulty::Hard:
        return HARD_FALL_INTERVAL_MS;
    }

    return NORMAL_FALL_INTERVAL_MS;
}

void GameSettings::SetDifficulty(GameDifficulty newDifficulty)
{
    difficulty = newDifficulty;
}
