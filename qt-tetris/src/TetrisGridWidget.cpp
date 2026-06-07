#include "TetrisGridWidget.h"
#include "model/Board.h"
#include "model/GameConfig.h"

#include <QKeyEvent>
#include <QPainter>
#include <QPaintEvent>
#include <QPushButton>

TetrisGridWidget::TetrisGridWidget(QWidget *parent)
    : QWidget(parent), m_controller(this)
{
    setWindowTitle("Tetris");
    setFixedSize(GameConfig::BOARD_WIDTH + GameConfig::STATUS_PANEL_WIDTH, GameConfig::BOARD_HEIGHT);
    setFocusPolicy(Qt::StrongFocus);

    connect(&m_controller, &TetrisController::GameUpdated, this, &TetrisGridWidget::OnGameUpdated);

    ConfigureSettingsButtons();
    m_controller.StartGame();
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
    m_renderer.RenderStatusPanel(painter, statusPanelRect, gameState.Score(), gameState.ClearedLineCount());

    if (m_controller.IsGameOver())
    {
        m_renderer.RenderGameOver(painter, rect());
    }

    event->accept();
}

void TetrisGridWidget::keyPressEvent(QKeyEvent *event)
{
    m_controller.HandleKeyPress(event);
}

void TetrisGridWidget::OnGameUpdated()
{
    update();
}

void TetrisGridWidget::ConfigureSettingsButtons()
{
    constexpr int BUTTON_LEFT_PADDING = 16;
    constexpr int BUTTON_TOP = 222;
    constexpr int BUTTON_HEIGHT = 30;
    constexpr int BUTTON_SPACING = 8;

    const int buttonX = GameConfig::BOARD_WIDTH + BUTTON_LEFT_PADDING;
    const int buttonWidth = GameConfig::STATUS_PANEL_WIDTH - (BUTTON_LEFT_PADDING * 2);

    m_easyButton = new QPushButton("Easy", this);
    m_normalButton = new QPushButton("Normal", this);
    m_hardButton = new QPushButton("Hard", this);

    m_easyButton->setGeometry(buttonX, BUTTON_TOP, buttonWidth, BUTTON_HEIGHT);
    m_normalButton->setGeometry(buttonX, BUTTON_TOP + BUTTON_HEIGHT + BUTTON_SPACING, buttonWidth, BUTTON_HEIGHT);
    m_hardButton->setGeometry(buttonX, BUTTON_TOP + ((BUTTON_HEIGHT + BUTTON_SPACING) * 2), buttonWidth, BUTTON_HEIGHT);

    m_easyButton->setFocusPolicy(Qt::NoFocus);
    m_normalButton->setFocusPolicy(Qt::NoFocus);
    m_hardButton->setFocusPolicy(Qt::NoFocus);

    connect(m_easyButton, &QPushButton::clicked, this, [this]() { SelectDifficulty(GameDifficulty::Easy); });
    connect(m_normalButton, &QPushButton::clicked, this, [this]() { SelectDifficulty(GameDifficulty::Normal); });
    connect(m_hardButton, &QPushButton::clicked, this, [this]() { SelectDifficulty(GameDifficulty::Hard); });

    UpdateDifficultyButtonStyles();
}

void TetrisGridWidget::SelectDifficulty(GameDifficulty difficulty)
{
    m_controller.SetDifficulty(difficulty);
    UpdateDifficultyButtonStyles();
    setFocus();
}

void TetrisGridWidget::UpdateDifficultyButtonStyles()
{
    const QString activeStyle = "QPushButton { background-color: #64b4ff; color: #101820; font-weight: bold; border: 1px solid #dcecff; padding: 4px; }";
    const QString inactiveStyle = "QPushButton { background-color: #3e4e60; color: white; border: 1px solid #6d7f95; padding: 4px; }"
                                  "QPushButton:hover { background-color: #4d6076; }";

    const GameDifficulty difficulty = m_controller.GetSettings().Difficulty();
    m_easyButton->setStyleSheet(difficulty == GameDifficulty::Easy ? activeStyle : inactiveStyle);
    m_normalButton->setStyleSheet(difficulty == GameDifficulty::Normal ? activeStyle : inactiveStyle);
    m_hardButton->setStyleSheet(difficulty == GameDifficulty::Hard ? activeStyle : inactiveStyle);
}
