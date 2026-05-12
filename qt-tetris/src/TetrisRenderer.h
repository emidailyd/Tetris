#pragma once

#include <QColor>
#include <QPainter>

#include "model/Tetromino.h"
#include "model/Board.h"

class TetrisRenderer
{
public:
    TetrisRenderer();

    void RenderGrid(QPainter &painter, int width, int height) const;
    void RenderBoard(QPainter &painter, const Board &board) const;
    void RenderActivePiece(QPainter &painter, const std::optional<Tetromino> &activePiece) const;
    void RenderGameOver(QPainter &painter, const QRect &rect) const;

    static QColor ColorForTetrominoType(TetrominoType type);
    static constexpr int CELL_SIZE = 28;

private:
    void DrawCell(QPainter &painter, int row, int column, const QColor &fillColor) const;
};