#include "TetrisGridWidget.h"
#include "model/Board.h"

#include <QKeyEvent>
#include <QPainter>
#include <QPaintEvent>

TetrisGridWidget::TetrisGridWidget(QWidget *parent)
    : QWidget(parent), m_controller(this)
{
    setWindowTitle("Tetris");
    setFixedSize(Board::COLUMN_COUNT * CellSize, Board::ROW_COUNT * CellSize);
    setFocusPolicy(Qt::StrongFocus);

    connect(&m_controller, &TetrisController::GameUpdated, this, &TetrisGridWidget::OnGameUpdated);

    m_controller.StartGame();
}

void TetrisGridWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, false);

    m_renderer.RenderGrid(painter, width(), height());
    m_renderer.RenderBoard(painter, m_controller.GetGameState().GameBoard());
    m_renderer.RenderActivePiece(painter, m_controller.GetGameState().ActivePiece());

    if (m_controller.IsGameOver())
    {
        m_renderer.RenderGameOver(painter, rect());
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
