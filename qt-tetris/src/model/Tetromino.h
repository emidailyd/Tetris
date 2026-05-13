#pragma once

#include <array>

struct Cell
{
    int row = 0;
    int column = 0;
};

enum class TetrominoType
{
    I,
    O,
    T,
    S,
    Z,
    J,
    L
};

class Tetromino
{
public:
    Tetromino();
    Tetromino(TetrominoType type, int row, int column);

    TetrominoType Type() const;
    int Row() const;
    int Column() const;
    int Rotation() const;

    std::array<Cell, 4> Cells() const;

    void MoveLeft();
    void MoveRight();
    void MoveDown();
    void RotateClockwise();

private:
    TetrominoType pieceType = TetrominoType::T;
    int positionRow = 0;
    int positionColumn = 0;
    int rotationIndex = 0;
};