#include "Tetromino.h"

namespace
{
std::array<Cell, 4> BaseOffsets(TetrominoType type)
{
    switch (type) {
    case TetrominoType::I:
        return {{{1, 0}, {1, 1}, {1, 2}, {1, 3}}};
    case TetrominoType::O:
        return {{{1, 1}, {1, 2}, {2, 1}, {2, 2}}};
    case TetrominoType::T:
        return {{{1, 1}, {2, 0}, {2, 1}, {2, 2}}};
    case TetrominoType::S:
        return {{{1, 1}, {1, 2}, {2, 0}, {2, 1}}};
    case TetrominoType::Z:
        return {{{1, 0}, {1, 1}, {2, 1}, {2, 2}}};
    case TetrominoType::J:
        return {{{1, 0}, {2, 0}, {2, 1}, {2, 2}}};
    case TetrominoType::L:
        return {{{1, 2}, {2, 0}, {2, 1}, {2, 2}}};
    }

    return {{{1, 1}, {2, 0}, {2, 1}, {2, 2}}};
}

std::array<Cell, 4> RotateOffsets(const std::array<Cell, 4>& offsets, int rotation)
{
    std::array<Cell, 4> rotatedOffsets = offsets;
    const int normalizedRotation = rotation % 4;

    for (int step = 0; step < normalizedRotation; ++step) {
        for (Cell& offset : rotatedOffsets) {
            const int previousRow = offset.row;
            offset.row = offset.column;
            offset.column = 3 - previousRow;
        }
    }

    return rotatedOffsets;
}
}

Tetromino::Tetromino()
    : Tetromino(TetrominoType::T, 0, 3)
{
}

Tetromino::Tetromino(TetrominoType type, int row, int column)
    : pieceType(type)
    , positionRow(row)
    , positionColumn(column)
{
}

TetrominoType Tetromino::Type() const
{
    return pieceType;
}

int Tetromino::Row() const
{
    return positionRow;
}

int Tetromino::Column() const
{
    return positionColumn;
}

int Tetromino::Rotation() const
{
    return rotationIndex;
}

std::array<Cell, 4> Tetromino::Cells() const
{
    const std::array<Cell, 4> rotatedOffsets = RotateOffsets(BaseOffsets(pieceType), rotationIndex);

    std::array<Cell, 4> absoluteCells{};
    for (int index = 0; index < static_cast<int>(absoluteCells.size()); ++index) {
        absoluteCells[static_cast<std::size_t>(index)].row = positionRow + rotatedOffsets[static_cast<std::size_t>(index)].row;
        absoluteCells[static_cast<std::size_t>(index)].column = positionColumn + rotatedOffsets[static_cast<std::size_t>(index)].column;
    }

    return absoluteCells;
}

void Tetromino::MoveLeft()
{
    --positionColumn;
}

void Tetromino::MoveRight()
{
    ++positionColumn;
}

void Tetromino::MoveDown()
{
    ++positionRow;
}

void Tetromino::RotateClockwise()
{
    rotationIndex = (rotationIndex + 1) % 4;
}