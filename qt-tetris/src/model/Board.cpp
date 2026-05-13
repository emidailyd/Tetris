#include "Board.h"

Board::Board()
{
    for (auto& row : boardCells) {
        row.fill(CellState::EMPTY);
    }
}

bool Board::IsInside(int row, int column) const
{
    return row >= 0 && row < ROW_COUNT && column >= 0 && column < COLUMN_COUNT;
}

bool Board::IsOccupied(int row, int column) const
{
    return IsInside(row, column) && boardCells[static_cast<std::size_t>(row)][static_cast<std::size_t>(column)] == CellState::FILLED;
}

bool Board::CanPlace(const Tetromino& tetromino) const
{
    const std::array<Cell, 4> occupiedCells = tetromino.Cells();
    for (const Cell& cell : occupiedCells) {
        if (!IsInside(cell.row, cell.column) || IsOccupied(cell.row, cell.column)) {
            return false;
        }
    }

    return true;
}

void Board::Place(const Tetromino& tetromino)
{
    const std::array<Cell, 4> occupiedCells = tetromino.Cells();
    for (const Cell& cell : occupiedCells) {
        if (IsInside(cell.row, cell.column)) {
            boardCells[static_cast<std::size_t>(cell.row)][static_cast<std::size_t>(cell.column)] = CellState::FILLED;
        }
    }
}

int Board::ClearCompletedLines()
{
    int clearedLines = 0;

    for (int row = ROW_COUNT - 1; row >= 0; --row) {
        bool lineIsComplete = true;
        for (int column = 0; column < COLUMN_COUNT; ++column) {
            if (boardCells[static_cast<std::size_t>(row)][static_cast<std::size_t>(column)] == CellState::EMPTY) {
                lineIsComplete = false;
                break;
            }
        }

        if (!lineIsComplete) {
            continue;
        }

        ++clearedLines;

        for (int movedRow = row; movedRow > 0; --movedRow) {
            boardCells[static_cast<std::size_t>(movedRow)] = boardCells[static_cast<std::size_t>(movedRow - 1)];
        }

        boardCells[0].fill(CellState::EMPTY);
        ++row;
    }

    return clearedLines;
}

const std::array<std::array<Board::CellState, Board::COLUMN_COUNT>, Board::ROW_COUNT>& Board::Cells() const
{
    return boardCells;
}