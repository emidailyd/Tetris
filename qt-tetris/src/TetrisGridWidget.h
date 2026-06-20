#pragma once

#include <QWidget>

#include "TetrisController.h"
#include "TetrisRenderer.h"

class QKeyEvent;
class QPaintEvent;
class QPushButton;
class QLabel;

class TetrisGridWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TetrisGridWidget(QWidget *parent = nullptr);

    void StartGame();
    void SetDifficulty(GameDifficulty difficulty);

signals:
    void GameOver(int finalScore);
    void ViewHighscoresRequested();
    void ReturnToMainMenuRequested();

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void OnGameUpdated();
    void OnGameOver(int finalScore);
    void OnPauseResume();
    void OnPauseRestart();
    void OnPauseReturnToMenu();

private:
    void CreatePauseOverlay();
    void CreateGameOverOverlay();
    void TogglePause();

    TetrisRenderer m_renderer;
    TetrisController m_controller;
    QWidget *m_pauseOverlay = nullptr;
    QPushButton *m_resumeButton = nullptr;
    QPushButton *m_restartButton = nullptr;
    QPushButton *m_mainMenuButton = nullptr;
    QWidget *m_gameOverOverlay = nullptr;
    QPushButton *m_playAgainButton = nullptr;
    QPushButton *m_viewScoresButton = nullptr;
    QPushButton *m_gameOverMenuButton = nullptr;
    QLabel *m_gameOverScoreLabel = nullptr;
};
