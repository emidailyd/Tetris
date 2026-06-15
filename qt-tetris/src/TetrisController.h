#pragma once

#include <QKeyEvent>
#include <QObject>
#include <QTimer>

#include "model/GameSettings.h"
#include "model/GameState.h"

class TetrisController : public QObject
{
    Q_OBJECT

public:
    explicit TetrisController(QObject *parent = nullptr);

    void HandleKeyPress(QKeyEvent *event);
    void StartGame();
    void ResetGame();
    void SetDifficulty(GameDifficulty difficulty);
    void SetPaused(bool paused);
    bool IsPaused() const { return m_paused; }

    const GameState &GetGameState() const { return m_gameState; }
    const GameSettings &GetSettings() const { return m_settings; }
    bool IsGameOver() const { return m_gameState.IsGameOver(); }

signals:
    void GameUpdated();
    void GameOver(int finalScore);

private slots:
    void AdvanceGame();

private:
    void ApplySettings();

    QTimer m_fallTimer;
    GameState m_gameState;
    GameSettings m_settings;
    bool m_hasEmittedGameOver = false;
    bool m_paused = false;
};
