#pragma once

#include <optional>
#include <random>

#include "Board.h"
#include "Tetromino.h"

class GameState
{
public:
    GameState();

    const Board& GameBoard() const;
    const std::optional<Tetromino>& ActivePiece() const;
    bool IsGameOver() const;

    void Reset();

    bool MoveActivePieceLeft();
    bool MoveActivePieceRight();
    bool MoveActivePieceDown();
    bool RotateActivePiece();

    bool StepDownOrLock();

private:
    Tetromino GenerateRandomPiece();
    bool SpawnNextPiece();
    bool TryApplyActivePiece(const Tetromino& candidatePiece);

    Board gameBoard;
    std::optional<Tetromino> activePiece;
    bool gameOver = false;
    std::mt19937 randomEngine;
};