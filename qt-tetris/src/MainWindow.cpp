#include "MainWindow.h"
#include "HighscoreManager.h"
#include "HighscoreWidget.h"
#include "MainMenuWidget.h"
#include "TetrisGridWidget.h"

#include <QStackedWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_highscoreManager = new HighscoreManager(this);
    m_highscoreManager->LoadHighscores();

    m_mainMenu = new MainMenuWidget(this);
    m_gameWidget = new TetrisGridWidget(this);
    m_highscoreWidget = new HighscoreWidget(m_highscoreManager, this);

    m_stack = new QStackedWidget(this);
    m_stack->addWidget(m_mainMenu);
    m_stack->addWidget(m_gameWidget);
    m_stack->addWidget(m_highscoreWidget);

    setCentralWidget(m_stack);
    setWindowTitle("Qt Tetris");
    setFixedSize(m_gameWidget->size());

    connect(m_mainMenu, &MainMenuWidget::StartGameRequested, this, &MainWindow::StartNewGame);
    connect(m_mainMenu, &MainMenuWidget::HighscoresRequested, this, &MainWindow::ShowHighscores);
    connect(m_mainMenu, &MainMenuWidget::ExitRequested, this, &MainWindow::OnExitRequested);

    connect(m_highscoreWidget, &HighscoreWidget::BackRequested, this, &MainWindow::ShowMainMenu);
    connect(m_gameWidget, &TetrisGridWidget::GameOver, this, &MainWindow::HandleGameOver);
    connect(m_gameWidget, &TetrisGridWidget::ReturnToMainMenuRequested, this, &MainWindow::ShowMainMenu);

    ShowMainMenu();
}

void MainWindow::ShowMainMenu()
{
    m_stack->setCurrentWidget(m_mainMenu);
}

void MainWindow::StartNewGame(GameDifficulty difficulty)
{
    m_gameWidget->SetDifficulty(difficulty);
    m_gameWidget->StartGame();
    m_stack->setCurrentWidget(m_gameWidget);
}

void MainWindow::ShowHighscores()
{
    m_highscoreWidget->UpdateDisplay(m_highscoreManager->GetTopScores());
    m_stack->setCurrentWidget(m_highscoreWidget);
}

void MainWindow::HandleGameOver(int finalScore)
{
    m_highscoreManager->AddScore(finalScore);
    m_highscoreWidget->UpdateDisplay(m_highscoreManager->GetTopScores());
    m_stack->setCurrentWidget(m_highscoreWidget);
}

void MainWindow::OnExitRequested()
{
    close();
}
