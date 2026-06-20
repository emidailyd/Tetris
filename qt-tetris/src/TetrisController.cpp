#include "TetrisController.h"

TetrisController::TetrisController(QObject *parent)
    : QObject(parent)
{
    connect(&m_fallTimer, &QTimer::timeout, this, &TetrisController::AdvanceGame);
    ApplySettings();
}

void TetrisController::HandleKeyPress(QKeyEvent *event)
{
    if (m_gameState.IsGameOver())
    {
        if (event->key() == Qt::Key_R)
        {
            ResetGame();
            emit GameUpdated();
        }
        event->accept();
        return;
    }

    bool updated = false;
    switch (event->key())
    {
    case Qt::Key_Left:
        updated = m_gameState.MoveActivePieceLeft();
        break;
    case Qt::Key_Right:
        updated = m_gameState.MoveActivePieceRight();
        break;
    case Qt::Key_Down:
        updated = m_gameState.MoveActivePieceDown();
        break;
    case Qt::Key_Up:
    case Qt::Key_Space:
        updated = m_gameState.RotateActivePiece();
        break;
    case Qt::Key_R:
        ResetGame();
        updated = true;
        break;
    default:
        return;
    }

    if (updated)
    {
        emit GameUpdated();
    }
    event->accept();
}

void TetrisController::StartGame()
{
    m_hasEmittedGameOver = false;
    m_paused = false;
    m_fallTimer.start();
    ResetGame();
}

void TetrisController::ResetGame()
{
    m_gameState.Reset();
    m_hasEmittedGameOver = false;
}

void TetrisController::SetPaused(bool paused)
{
    if (m_paused == paused)
    {
        return;
    }

    m_paused = paused;
    if (m_paused)
    {
        m_fallTimer.stop();
    }
    else if (!m_gameState.IsGameOver())
    {
        m_fallTimer.start();
    }
}

void TetrisController::SetDifficulty(GameDifficulty difficulty)
{
    if (m_settings.Difficulty() == difficulty)
    {
        return;
    }

    m_settings.SetDifficulty(difficulty);
    ApplySettings();
    emit GameUpdated();
}

void TetrisController::ApplySettings()
{
    m_fallTimer.setInterval(m_settings.FallIntervalMs());
}

void TetrisController::AdvanceGame()
{
    if (m_paused)
    {
        return;
    }

    if (m_gameState.IsGameOver())
    {
        m_fallTimer.stop();
        return;
    }

    m_gameState.StepDownOrLock();
    emit GameUpdated();

    if (m_gameState.IsGameOver() && !m_hasEmittedGameOver)
    {
        m_hasEmittedGameOver = true;
        emit GameOver(m_gameState.Score());
    }
}
