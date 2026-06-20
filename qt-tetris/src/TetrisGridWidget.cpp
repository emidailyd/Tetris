#include "TetrisGridWidget.h"
#include "model/Board.h"
#include "model/GameConfig.h"

#include <QKeyEvent>
#include <QPainter>
#include <QPaintEvent>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

TetrisGridWidget::TetrisGridWidget(QWidget *parent)
    : QWidget(parent), m_controller(this)
{
    setWindowTitle("Tetris");
    setFixedSize(GameConfig::BOARD_WIDTH + GameConfig::STATUS_PANEL_WIDTH, GameConfig::BOARD_HEIGHT);
    setFocusPolicy(Qt::StrongFocus);

    connect(&m_controller, &TetrisController::GameUpdated, this, &TetrisGridWidget::OnGameUpdated);
    connect(&m_controller, &TetrisController::GameOver, this, &TetrisGridWidget::OnGameOver);

    CreatePauseOverlay();
    CreateGameOverOverlay();
}

void TetrisGridWidget::StartGame()
{
    m_pauseOverlay->hide();
    m_gameOverOverlay->hide();
    m_controller.StartGame();
    setFocus();
    update();
}

void TetrisGridWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, false);

    const GameState &gameState = m_controller.GetGameState();
    const QRect statusPanelRect(GameConfig::BOARD_WIDTH, 0, GameConfig::STATUS_PANEL_WIDTH, height());

    m_renderer.RenderGrid(painter, GameConfig::BOARD_WIDTH, GameConfig::BOARD_HEIGHT);
    m_renderer.RenderBoard(painter, gameState.GameBoard());
    m_renderer.RenderActivePiece(painter, gameState.ActivePiece());
    m_renderer.RenderStatusPanel(painter, statusPanelRect, gameState.Score(), gameState.ClearedLineCount(), m_controller.GetSettings().Difficulty());

    event->accept();
}

void TetrisGridWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape && !m_controller.IsGameOver())
    {
        TogglePause();
        event->accept();
        return;
    }

    if (m_controller.IsPaused())
    {
        event->accept();
        return;
    }

    m_controller.HandleKeyPress(event);
}

void TetrisGridWidget::OnGameUpdated()
{
    update();
}

void TetrisGridWidget::OnGameOver(int finalScore)
{
    if (m_gameOverScoreLabel)
    {
        m_gameOverScoreLabel->setText(QString::number(finalScore));
    }
    m_gameOverOverlay->show();
    m_gameOverOverlay->raise();
    emit GameOver(finalScore);
}

void TetrisGridWidget::CreatePauseOverlay()
{
    m_pauseOverlay = new QWidget(this);
    m_pauseOverlay->setGeometry(0, 0, width(), height());
    m_pauseOverlay->setStyleSheet("background-color: rgba(0, 0, 0, 180);");
    m_pauseOverlay->hide();

    QLabel *pauseLabel = new QLabel("Paused", m_pauseOverlay);
    pauseLabel->setAlignment(Qt::AlignCenter);
    pauseLabel->setStyleSheet("color: white; font-size: 28px; font-weight: bold;");

    m_resumeButton = new QPushButton("Resume", m_pauseOverlay);
    m_restartButton = new QPushButton("Restart", m_pauseOverlay);
    m_mainMenuButton = new QPushButton("Main Menu", m_pauseOverlay);

    m_resumeButton->setFixedHeight(36);
    m_restartButton->setFixedHeight(36);
    m_mainMenuButton->setFixedHeight(36);
    m_resumeButton->setFocusPolicy(Qt::NoFocus);
    m_restartButton->setFocusPolicy(Qt::NoFocus);
    m_mainMenuButton->setFocusPolicy(Qt::NoFocus);

    connect(m_resumeButton, &QPushButton::clicked, this, &TetrisGridWidget::OnPauseResume);
    connect(m_restartButton, &QPushButton::clicked, this, &TetrisGridWidget::OnPauseRestart);
    connect(m_mainMenuButton, &QPushButton::clicked, this, &TetrisGridWidget::OnPauseReturnToMenu);

    QVBoxLayout *overlayLayout = new QVBoxLayout(m_pauseOverlay);
    overlayLayout->setAlignment(Qt::AlignCenter);
    overlayLayout->setSpacing(16);
    overlayLayout->addWidget(pauseLabel);
    overlayLayout->addWidget(m_resumeButton);
    overlayLayout->addWidget(m_restartButton);
    overlayLayout->addWidget(m_mainMenuButton);
    overlayLayout->setContentsMargins(80, 80, 80, 80);
}

void TetrisGridWidget::TogglePause()
{
    const bool paused = !m_controller.IsPaused();
    m_controller.SetPaused(paused);
    m_pauseOverlay->setVisible(paused);
    if (paused)
    {
        m_pauseOverlay->raise();
    }
    else
    {
        setFocus();
    }
    update();
}

void TetrisGridWidget::OnPauseResume()
{
    TogglePause();
}

void TetrisGridWidget::OnPauseRestart()
{
    m_pauseOverlay->hide();
    m_controller.StartGame();
    update();
}

void TetrisGridWidget::OnPauseReturnToMenu()
{
    m_pauseOverlay->hide();
    m_controller.SetPaused(true);
    emit ReturnToMainMenuRequested();
}

void TetrisGridWidget::SetDifficulty(GameDifficulty difficulty)
{
    m_controller.SetDifficulty(difficulty);
}

void TetrisGridWidget::CreateGameOverOverlay()
{
    m_gameOverOverlay = new QWidget(this);
    m_gameOverOverlay->setGeometry(0, 0, width(), height());
    m_gameOverOverlay->setStyleSheet("background-color: rgba(0, 0, 0, 180);");
    m_gameOverOverlay->hide();

    QLabel *gameOverLabel = new QLabel("Game Over", m_gameOverOverlay);
    gameOverLabel->setAlignment(Qt::AlignCenter);
    gameOverLabel->setStyleSheet("color: white; font-size: 32px; font-weight: bold; margin-bottom: 20px;");

    m_gameOverScoreLabel = new QLabel(m_gameOverOverlay);
    m_gameOverScoreLabel->setAlignment(Qt::AlignCenter);
    m_gameOverScoreLabel->setStyleSheet("color: #64b4ff; font-size: 24px; font-weight: bold; margin-bottom: 24px;");

    m_playAgainButton = new QPushButton("Play Again", m_gameOverOverlay);
    m_viewScoresButton = new QPushButton("View Highscores", m_gameOverOverlay);
    m_gameOverMenuButton = new QPushButton("Main Menu", m_gameOverOverlay);

    m_playAgainButton->setFixedHeight(36);
    m_viewScoresButton->setFixedHeight(36);
    m_gameOverMenuButton->setFixedHeight(36);
    m_playAgainButton->setFocusPolicy(Qt::NoFocus);
    m_viewScoresButton->setFocusPolicy(Qt::NoFocus);
    m_gameOverMenuButton->setFocusPolicy(Qt::NoFocus);

    connect(m_playAgainButton, &QPushButton::clicked, this, [this]()
            {
        m_gameOverOverlay->hide();
        StartGame(); });
    connect(m_viewScoresButton, &QPushButton::clicked, this, [this]()
            {
        m_gameOverOverlay->hide();
        emit ViewHighscoresRequested(); });
    connect(m_gameOverMenuButton, &QPushButton::clicked, this, [this]()
            {
        m_gameOverOverlay->hide();
        emit ReturnToMainMenuRequested(); });

    QVBoxLayout *overlayLayout = new QVBoxLayout(m_gameOverOverlay);
    overlayLayout->setAlignment(Qt::AlignCenter);
    overlayLayout->setSpacing(16);
    overlayLayout->addWidget(gameOverLabel);
    overlayLayout->addWidget(m_gameOverScoreLabel);
    overlayLayout->addSpacing(16);
    overlayLayout->addWidget(m_playAgainButton);
    overlayLayout->addWidget(m_viewScoresButton);
    overlayLayout->addWidget(m_gameOverMenuButton);
    overlayLayout->setContentsMargins(80, 80, 80, 80);
}
