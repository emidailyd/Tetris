#include "TetrisGridWidget.h"
#include "model/Board.h"
#include "model/GameConfig.h"

#include <QKeyEvent>
#include <QPainter>
#include <QPaintEvent>

TetrisGridWidget::TetrisGridWidget(QWidget *parent)
    : QWidget(parent), m_controller(this)
{
    setWindowTitle("Tetris");
    setFixedSize(GameConfig::BOARD_WIDTH + GameConfig::STATUS_PANEL_WIDTH, GameConfig::BOARD_HEIGHT);
    setFocusPolicy(Qt::StrongFocus);

    connect(&m_controller, &TetrisController::GameUpdated, this, &TetrisGridWidget::OnGameUpdated);
    connect(&m_controller, &TetrisController::GameOver, this, &TetrisGridWidget::OnGameOver);
}

void TetrisGridWidget::StartGame()
{
    m_controller.StartGame();
    setFocus();
    update();
}

void TetrisGridWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, false);

    const GameState &gameState = m_controller.GetGameState();
    const QRect statusPanelRect(GameConfig::BOARD_WIDTH, 0, GameConfig::STATUS_PANEL_WIDTH, height());

    m_renderer.RenderGrid(painter, GameConfig::BOARD_WIDTH, GameConfig::BOARD_HEIGHT);
    m_renderer.RenderBoard(painter, gameState.GameBoard());
    m_renderer.RenderActivePiece(painter, gameState.ActivePiece());
    m_renderer.RenderStatusPanel(painter, statusPanelRect, gameState.Score(), gameState.ClearedLineCount(), m_controller.GetSettings().Difficulty());

    if (m_controller.IsGameOver())
    {
        m_renderer.RenderGameOver(painter, QRect(0, 0, GameConfig::BOARD_WIDTH, GameConfig::BOARD_HEIGHT));
    }

    event->accept();
}

void TetrisGridWidget::keyPressEvent(QKeyEvent *event)
{
    m_controller.HandleKeyPress(event);
}

void TetrisGridWidget::OnGameUpdated()
{
    update();
}

void TetrisGridWidget::OnGameOver(int finalScore)
{
    emit GameOver(finalScore);
}

void TetrisGridWidget::SetDifficulty(GameDifficulty difficulty)
{
    m_controller.SetDifficulty(difficulty);
}
