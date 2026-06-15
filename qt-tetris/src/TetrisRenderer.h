#pragma once

#include <optional>
#include <QColor>
#include <QPainter>
#include <QRect>

#include "model/Tetromino.h"
#include "model/Board.h"

enum class GameDifficulty;

class TetrisRenderer
{
public:
    TetrisRenderer();

    void RenderGrid(QPainter &painter, int width, int height) const;
    void RenderBoard(QPainter &painter, const Board &board) const;
    void RenderActivePiece(QPainter &painter, const std::optional<Tetromino> &activePiece) const;
    void RenderStatusPanel(QPainter &painter, const QRect &rect, int score, int clearedLineCount, GameDifficulty difficulty) const;
    void RenderGameOver(QPainter &painter, const QRect &rect) const;

    static QColor ColorForTetrominoType(TetrominoType type);

private:
    void DrawCell(QPainter &painter, int row, int column, const QColor &fillColor) const;
};
