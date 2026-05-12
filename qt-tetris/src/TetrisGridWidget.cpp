#include "TetrisGridWidget.h"

#include <QKeyEvent>
#include <QPainter>
#include <QPaintEvent>
#include <QPen>

namespace
{
    QColor colorForTetrominoType(TetrominoType type)
    {
        switch (type)
        {
        case TetrominoType::I:
            return QColor(0, 204, 255);
        case TetrominoType::O:
            return QColor(255, 204, 0);
        case TetrominoType::T:
            return QColor(180, 0, 255);
        case TetrominoType::S:
            return QColor(0, 204, 0);
        case TetrominoType::Z:
            return QColor(255, 51, 51);
        case TetrominoType::J:
            return QColor(0, 51, 153);
        case TetrominoType::L:
            return QColor(255, 128, 0);
        }

        return QColor(255, 255, 255);
    }
}

TetrisGridWidget::TetrisGridWidget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Tetris");
    setFixedSize(kColumns * kCellSize, kRows * kCellSize);
    setFocusPolicy(Qt::StrongFocus);

    connect(&m_fallTimer, &QTimer::timeout, this, &TetrisGridWidget::advanceGame);
    m_fallTimer.setInterval(300);
    m_fallTimer.start();

    resetGame();
}

void TetrisGridWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, false);

    painter.fillRect(rect(), QColor(18, 26, 38));

    QPen gridPen(QColor(62, 78, 96));
    gridPen.setWidth(1);
    painter.setPen(gridPen);

    for (int column = 0; column <= kColumns; ++column)
    {
        const int x = column * kCellSize;
        painter.drawLine(x, 0, x, height());
    }

    for (int row = 0; row <= kRows; ++row)
    {
        const int y = row * kCellSize;
        painter.drawLine(0, y, width(), y);
    }

    const auto &cells = m_gameState.GameBoard().Cells();
    for (int row = 0; row < kRows; ++row)
    {
        for (int column = 0; column < kColumns; ++column)
        {
            if (cells[static_cast<std::size_t>(row)][static_cast<std::size_t>(column)] == Board::CellState::FILLED)
            {
                drawCell(painter, row, column, QColor(100, 180, 255));
            }
        }
    }

    if (const auto &activePiece = m_gameState.ActivePiece(); activePiece.has_value())
    {
        const QColor activeColor = colorForTetrominoType(activePiece->Type());
        for (const Cell &cell : activePiece->Cells())
        {
            if (cell.row >= 0 && cell.row < kRows && cell.column >= 0 && cell.column < kColumns)
            {
                drawCell(painter, cell.row, cell.column, activeColor);
            }
        }
    }

    if (m_gameState.IsGameOver())
    {
        painter.fillRect(rect(), QColor(0, 0, 0, 160));
        painter.setPen(Qt::white);
        painter.setFont(QFont("Arial", 18, QFont::Bold));
        painter.drawText(rect(), Qt::AlignCenter, "Game Over\nPress R to restart");
    }

    event->accept();
}

void TetrisGridWidget::keyPressEvent(QKeyEvent *event)
{
    if (m_gameState.IsGameOver())
    {
        if (event->key() == Qt::Key_R)
        {
            resetGame();
            update();
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
        resetGame();
        updated = true;
        break;
    default:
        QWidget::keyPressEvent(event);
        return;
    }

    if (updated)
    {
        update();
    }
    event->accept();
}

void TetrisGridWidget::advanceGame()
{
    if (m_gameState.IsGameOver())
    {
        return;
    }

    m_gameState.StepDownOrLock();
    update();
}

void TetrisGridWidget::resetGame()
{
    m_gameState.Reset();
}

void TetrisGridWidget::drawCell(QPainter &painter, int row, int column, const QColor &fillColor) const
{
    const QRect cellRect(
        column * kCellSize,
        row * kCellSize,
        kCellSize,
        kCellSize);

    painter.fillRect(cellRect.adjusted(2, 2, -2, -2), fillColor);
    painter.setPen(QPen(QColor(220, 220, 220), 1));
    painter.drawRect(cellRect.adjusted(2, 2, -2, -2));
}
