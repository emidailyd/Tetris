#include "TetrisRenderer.h"

#include <QFont>
#include <QPen>

TetrisRenderer::TetrisRenderer()
{
}

void TetrisRenderer::RenderGrid(QPainter &painter, int width, int height) const
{
    painter.fillRect(0, 0, width, height, QColor(18, 26, 38));

    QPen gridPen(QColor(62, 78, 96));
    gridPen.setWidth(1);
    painter.setPen(gridPen);

    for (int column = 0; column <= kColumns; ++column)
    {
        const int x = column * kCellSize;
        painter.drawLine(x, 0, x, height);
    }

    for (int row = 0; row <= kRows; ++row)
    {
        const int y = row * kCellSize;
        painter.drawLine(0, y, width, y);
    }
}

void TetrisRenderer::RenderBoard(QPainter &painter, const Board &board) const
{
    const auto &cells = board.Cells();
    for (int row = 0; row < kRows; ++row)
    {
        for (int column = 0; column < kColumns; ++column)
        {
            if (cells[static_cast<std::size_t>(row)][static_cast<std::size_t>(column)] == Board::CellState::FILLED)
            {
                DrawCell(painter, row, column, QColor(100, 180, 255));
            }
        }
    }
}

void TetrisRenderer::RenderActivePiece(QPainter &painter, const std::optional<Tetromino> &activePiece) const
{
    if (!activePiece.has_value())
        return;

    const QColor activeColor = ColorForTetrominoType(activePiece->Type());
    for (const Cell &cell : activePiece->Cells())
    {
        if (cell.row >= 0 && cell.row < kRows && cell.column >= 0 && cell.column < kColumns)
        {
            DrawCell(painter, cell.row, cell.column, activeColor);
        }
    }
}

void TetrisRenderer::RenderGameOver(QPainter &painter, const QRect &rect) const
{
    painter.fillRect(rect, QColor(0, 0, 0, 160));
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 18, QFont::Bold));
    painter.drawText(rect, Qt::AlignCenter, "Game Over\nPress R to restart");
}

QColor TetrisRenderer::ColorForTetrominoType(TetrominoType type)
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

void TetrisRenderer::DrawCell(QPainter &painter, int row, int column, const QColor &fillColor) const
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