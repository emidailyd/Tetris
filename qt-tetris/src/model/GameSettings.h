#pragma once

enum class GameDifficulty
{
    Easy,
    Normal,
    Hard
};

class GameSettings
{
public:
    GameSettings();

    GameDifficulty Difficulty() const;
    int FallIntervalMs() const;

    void SetDifficulty(GameDifficulty newDifficulty);

private:
    GameDifficulty difficulty;
};
