#include "GameState.h"

#include <array>

namespace
{
constexpr std::array<TetrominoType, 7> PIECE_TYPES = {
    TetrominoType::I,
    TetrominoType::O,
    TetrominoType::T,
    TetrominoType::S,
    TetrominoType::Z,
    TetrominoType::J,
    TetrominoType::L,
};

int ScoreForLineClear(int clearedLines)
{
    switch (clearedLines) {
    case 1:
        return 100;
    case 2:
        return 300;
    case 3:
        return 500;
    case 4:
        return 800;
    default:
        return 0;
    }
}
}

GameState::GameState()
    : randomEngine(std::random_device{}())
{
    Reset();
}

const Board& GameState::GameBoard() const
{
    return gameBoard;
}

const std::optional<Tetromino>& GameState::ActivePiece() const
{
    return activePiece;
}

bool GameState::IsGameOver() const
{
    return gameOver;
}

int GameState::Score() const
{
    return score;
}

int GameState::ClearedLineCount() const
{
    return clearedLineCount;
}

void GameState::Reset()
{
    gameBoard = Board();
    activePiece.reset();
    gameOver = false;
    score = 0;
    clearedLineCount = 0;
    SpawnNextPiece();
}

bool GameState::MoveActivePieceLeft()
{
    if (!activePiece.has_value() || gameOver) {
        return false;
    }

    Tetromino candidatePiece = *activePiece;
    candidatePiece.MoveLeft();
    return TryApplyActivePiece(candidatePiece);
}

bool GameState::MoveActivePieceRight()
{
    if (!activePiece.has_value() || gameOver) {
        return false;
    }

    Tetromino candidatePiece = *activePiece;
    candidatePiece.MoveRight();
    return TryApplyActivePiece(candidatePiece);
}

bool GameState::MoveActivePieceDown()
{
    if (!activePiece.has_value() || gameOver) {
        return false;
    }

    Tetromino candidatePiece = *activePiece;
    candidatePiece.MoveDown();
    return TryApplyActivePiece(candidatePiece);
}

bool GameState::RotateActivePiece()
{
    if (!activePiece.has_value() || gameOver) {
        return false;
    }

    Tetromino candidatePiece = *activePiece;
    candidatePiece.RotateClockwise();
    return TryApplyActivePiece(candidatePiece);
}

bool GameState::StepDownOrLock()
{
    if (!activePiece.has_value() || gameOver) {
        return false;
    }

    if (MoveActivePieceDown()) {
        return true;
    }

    gameBoard.Place(*activePiece);
    const int linesClearedNow = gameBoard.ClearCompletedLines();
    clearedLineCount += linesClearedNow;
    score += ScoreForLineClear(linesClearedNow);

    activePiece.reset();
    SpawnNextPiece();
    return true;
}

Tetromino GameState::GenerateRandomPiece()
{
    std::uniform_int_distribution<int> distribution(0, static_cast<int>(PIECE_TYPES.size()) - 1);
    const TetrominoType randomType = PIECE_TYPES[static_cast<std::size_t>(distribution(randomEngine))];

    // spawn at the top center 
    return Tetromino(randomType, 0, (Board::COLUMN_COUNT / 2) - 2);
}

bool GameState::SpawnNextPiece()
{
    Tetromino nextPiece = GenerateRandomPiece();
    if (!gameBoard.CanPlace(nextPiece)) {
        gameOver = true;
        return false;
    }

    activePiece = nextPiece;
    return true;
}

bool GameState::TryApplyActivePiece(const Tetromino& candidatePiece)
{
    if (!gameBoard.CanPlace(candidatePiece)) {
        return false;
    }

    activePiece = candidatePiece;
    return true;
}