#include "HighscoreManager.h"

#include <algorithm>
#include <QDir>
#include <QFile>
#include <QStandardPaths>
#include <QTextStream>

namespace
{
    constexpr int MAX_HIGHSCORES = 10;
}

HighscoreManager::HighscoreManager(QObject *parent)
{
    const QString appDataLocation = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    const QDir appDataDir(appDataLocation);

    if (!appDataDir.exists())
    {
        QDir().mkpath(appDataLocation);
    }

    m_filePath = appDataDir.filePath("highscores.txt");
}

void HighscoreManager::LoadHighscores()
{
    m_highscores.clear();

    QFile file(m_filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd())
    {
        const QString line = in.readLine().trimmed();
        bool ok = false;
        const int score = line.toInt(&ok);
        if (ok)
        {
            m_highscores.push_back(score);
        }
    }

    std::sort(m_highscores.begin(), m_highscores.end(), std::greater<>());
    if (m_highscores.size() > MAX_HIGHSCORES)
    {
        m_highscores.resize(MAX_HIGHSCORES);
    }
}

void HighscoreManager::SaveHighscores() const
{
    EnsureDataDirectoryExists();

    QFile file(m_filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return;
    }

    QTextStream out(&file);
    for (int score : m_highscores)
    {
        out << score << '\n';
    }
}

void HighscoreManager::AddScore(int score)
{
    m_highscores.push_back(score);
    std::sort(m_highscores.begin(), m_highscores.end(), std::greater<>());
    if (m_highscores.size() > MAX_HIGHSCORES)
    {
        m_highscores.resize(MAX_HIGHSCORES);
    }

    SaveHighscores();
}

std::vector<int> HighscoreManager::GetTopScores() const
{
    return m_highscores;
}

void HighscoreManager::EnsureDataDirectoryExists() const
{
    const QString appDataLocation = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(appDataLocation);
}
