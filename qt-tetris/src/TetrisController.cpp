#include "TetrisController.h"

TetrisController::TetrisController(QObject *parent)
    : QObject(parent)
{
    connect(&m_fallTimer, &QTimer::timeout, this, &TetrisController::AdvanceGame);
    m_fallTimer.setInterval(300);
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
    m_fallTimer.start();
    ResetGame();
}

void TetrisController::ResetGame()
{
    m_gameState.Reset();
}

void TetrisController::AdvanceGame()
{
    if (m_gameState.IsGameOver())
    {
        return;
    }

    m_gameState.StepDownOrLock();
    emit GameUpdated();
}