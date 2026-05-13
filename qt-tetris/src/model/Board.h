#pragma once

#include <array>

#include "Tetromino.h"

class Board
{
public:
    static constexpr int ROW_COUNT = 20;
    static constexpr int COLUMN_COUNT = 10;

    enum class CellState
    {
        EMPTY,
        FILLED
    };

    Board();

    bool IsInside(int row, int column) const;
    bool IsOccupied(int row, int column) const;
    bool CanPlace(const Tetromino& tetromino) const;

    void Place(const Tetromino& tetromino);
    int ClearCompletedLines();

    const std::array<std::array<CellState, COLUMN_COUNT>, ROW_COUNT>& Cells() const;

private:
    std::array<std::array<CellState, COLUMN_COUNT>, ROW_COUNT> boardCells{};
};