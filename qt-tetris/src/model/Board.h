#pragma once

#include <array>

#include "Tetromino.h"
#include "GameConfig.h"

class Board
{
public:
    enum class CellState
    {
        EMPTY,
        FILLED
    };

    Board();

    bool IsInside(int row, int column) const;
    bool IsOccupied(int row, int column) const;
    bool CanPlace(const Tetromino &tetromino) const;

    void Place(const Tetromino &tetromino);
    int ClearCompletedLines();

    const std::array<std::array<CellState, GameConfig::COLUMN_COUNT>, GameConfig::ROW_COUNT> &Cells() const;

private:
    std::array<std::array<CellState, GameConfig::COLUMN_COUNT>, GameConfig::ROW_COUNT> boardCells{};
};