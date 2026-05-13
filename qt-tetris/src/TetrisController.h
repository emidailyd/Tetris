#pragma once

#include <QKeyEvent>
#include <QObject>
#include <QTimer>

#include "model/GameState.h"

class TetrisController : public QObject
{
    Q_OBJECT

public:
    explicit TetrisController(QObject *parent = nullptr);

    void HandleKeyPress(QKeyEvent *event);
    void StartGame();
    void ResetGame();

    const GameState &GetGameState() const { return m_gameState; }
    bool IsGameOver() const { return m_gameState.IsGameOver(); }

signals:
    void GameUpdated();

private slots:
    void AdvanceGame();

private:
    QTimer m_fallTimer;
    GameState m_gameState;
};