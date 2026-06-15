#include "TetrisRenderer.h"
#include "model/GameConfig.h"
#include "model/GameSettings.h"

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

    for (int column = 0; column <= GameConfig::COLUMN_COUNT; ++column)
    {
        const int x = column * GameConfig::CELL_SIZE;
        painter.drawLine(x, 0, x, height);
    }

    for (int row = 0; row <= GameConfig::ROW_COUNT; ++row)
    {
        const int y = row * GameConfig::CELL_SIZE;
        painter.drawLine(0, y, width, y);
    }
}

void TetrisRenderer::RenderBoard(QPainter &painter, const Board &board) const
{
    const auto &cells = board.Cells();
    for (int row = 0; row < GameConfig::ROW_COUNT; ++row)
    {
        for (int column = 0; column < GameConfig::COLUMN_COUNT; ++column)
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
        if (cell.row >= 0 && cell.row < GameConfig::ROW_COUNT && cell.column >= 0 && cell.column < GameConfig::COLUMN_COUNT)
        {
            DrawCell(painter, cell.row, cell.column, activeColor);
        }
    }
}

static QString DifficultyToString(GameDifficulty difficulty)
{
    switch (difficulty)
    {
    case GameDifficulty::Easy:
        return QStringLiteral("Easy");
    case GameDifficulty::Normal:
        return QStringLiteral("Normal");
    case GameDifficulty::Hard:
        return QStringLiteral("Hard");
    }

    return QStringLiteral("Normal");
}

void TetrisRenderer::RenderStatusPanel(QPainter &painter, const QRect &rect, int score, int clearedLineCount, GameDifficulty difficulty) const
{
    painter.fillRect(rect, QColor(28, 36, 50));

    painter.setPen(QColor(210, 224, 240));
    painter.setFont(QFont("Arial", 14, QFont::Bold));
    painter.drawText(rect.adjusted(16, 22, -16, -16), Qt::AlignLeft | Qt::AlignTop, "Score");

    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 18, QFont::Bold));
    painter.drawText(rect.adjusted(16, 50, -16, -16), Qt::AlignLeft | Qt::AlignTop, QString::number(score));

    painter.setPen(QColor(210, 224, 240));
    painter.setFont(QFont("Arial", 14, QFont::Bold));
    painter.drawText(rect.adjusted(16, 110, -16, -16), Qt::AlignLeft | Qt::AlignTop, "Lines");

    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 18, QFont::Bold));
    painter.drawText(rect.adjusted(16, 138, -16, -16), Qt::AlignLeft | Qt::AlignTop, QString::number(clearedLineCount));

    painter.setPen(QColor(210, 224, 240));
    painter.setFont(QFont("Arial", 14, QFont::Bold));
    painter.drawText(rect.adjusted(16, 190, -16, -16), Qt::AlignLeft | Qt::AlignTop, "Difficulty");

    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 18, QFont::Bold));
    painter.drawText(rect.adjusted(16, 218, -16, -16), Qt::AlignLeft | Qt::AlignTop, DifficultyToString(difficulty));
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
        column * GameConfig::CELL_SIZE,
        row * GameConfig::CELL_SIZE,
        GameConfig::CELL_SIZE,
        GameConfig::CELL_SIZE);

    painter.fillRect(cellRect.adjusted(2, 2, -2, -2), fillColor);
    painter.setPen(QPen(QColor(220, 220, 220), 1));
    painter.drawRect(cellRect.adjusted(2, 2, -2, -2));
}
