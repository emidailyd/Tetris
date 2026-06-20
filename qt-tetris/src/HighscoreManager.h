#pragma once

#include <vector>
#include <QString>

class QObject;

class HighscoreManager
{
public:
    HighscoreManager(QObject *parent = nullptr);

    void LoadHighscores();
    void SaveHighscores() const;
    void AddScore(int score);
    std::vector<int> GetTopScores() const;

private:
    void EnsureDataDirectoryExists() const;

    std::vector<int> m_highscores;
    QString m_filePath;
};
