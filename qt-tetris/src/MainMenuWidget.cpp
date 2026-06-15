#include "MainMenuWidget.h"
#include "model/GameSettings.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

namespace
{
    const QString activeStyle = "QPushButton { background-color: #64b4ff; color: #101820; font-weight: bold; border: 1px solid #dcecff; border-radius: 4px; padding: 8px; }"
                                "QPushButton:hover { background-color: #7bc1ff; }";
    const QString inactiveStyle = "QPushButton { background-color: #334155; color: #f4f7fb; border: 1px solid #708198; border-radius: 4px; padding: 8px; }"
                                  "QPushButton:hover { background-color: #41536a; border-color: #9fb3ca; }";
}

MainMenuWidget::MainMenuWidget(QWidget *parent)
    : QWidget(parent)
{
    m_titleLabel = new QLabel("Qt Tetris", this);
    m_titleLabel->setAlignment(Qt::AlignCenter);
    m_titleLabel->setStyleSheet("font-size: 32px; font-weight: bold; color: white;");

    m_easyButton = new QPushButton("Easy", this);
    m_normalButton = new QPushButton("Normal", this);
    m_hardButton = new QPushButton("Hard", this);
    m_startButton = new QPushButton("Start Game", this);
    m_highscoreButton = new QPushButton("Highscores", this);
    m_exitButton = new QPushButton("Exit", this);

    m_easyButton->setFixedHeight(36);
    m_normalButton->setFixedHeight(36);
    m_hardButton->setFixedHeight(36);
    m_startButton->setFixedHeight(40);
    m_highscoreButton->setFixedHeight(40);
    m_exitButton->setFixedHeight(40);

    m_easyButton->setFocusPolicy(Qt::NoFocus);
    m_normalButton->setFocusPolicy(Qt::NoFocus);
    m_hardButton->setFocusPolicy(Qt::NoFocus);
    m_startButton->setFocusPolicy(Qt::NoFocus);
    m_highscoreButton->setFocusPolicy(Qt::NoFocus);
    m_exitButton->setFocusPolicy(Qt::NoFocus);

    connect(m_easyButton, &QPushButton::clicked, this, [this]()
            {
        m_selectedDifficulty = GameDifficulty::Easy;
        UpdateDifficultyButtonStyles();
        m_difficultyOptionsWidget->setVisible(false); });
    connect(m_normalButton, &QPushButton::clicked, this, [this]()
            {
        m_selectedDifficulty = GameDifficulty::Normal;
        UpdateDifficultyButtonStyles();
        m_difficultyOptionsWidget->setVisible(false); });
    connect(m_hardButton, &QPushButton::clicked, this, [this]()
            {
        m_selectedDifficulty = GameDifficulty::Hard;
        UpdateDifficultyButtonStyles();
        m_difficultyOptionsWidget->setVisible(false); });

    connect(m_startButton, &QPushButton::clicked, this, [this]()
            { emit StartGameRequested(m_selectedDifficulty); });
    connect(m_highscoreButton, &QPushButton::clicked, this, &MainMenuWidget::HighscoresRequested);
    connect(m_exitButton, &QPushButton::clicked, this, &MainMenuWidget::ExitRequested);

    m_difficultyButton = new QPushButton(this);
    m_difficultyButton->setFixedHeight(40);
    m_difficultyButton->setFocusPolicy(Qt::NoFocus);
    connect(m_difficultyButton, &QPushButton::clicked, this, [this]()
            { m_difficultyOptionsWidget->setVisible(!m_difficultyOptionsWidget->isVisible()); });

    QHBoxLayout *difficultyLayout = new QHBoxLayout;
    difficultyLayout->setSpacing(12);
    difficultyLayout->addWidget(m_easyButton);
    difficultyLayout->addWidget(m_normalButton);
    difficultyLayout->addWidget(m_hardButton);

    m_difficultyOptionsWidget = new QWidget(this);
    m_difficultyOptionsWidget->setLayout(difficultyLayout);
    m_difficultyOptionsWidget->setVisible(false);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(16);
    layout->addWidget(m_titleLabel);
    layout->addSpacing(24);
    layout->addWidget(m_difficultyButton);
    layout->addWidget(m_difficultyOptionsWidget);
    layout->addWidget(m_startButton);
    layout->addWidget(m_highscoreButton);
    layout->addWidget(m_exitButton);
    layout->setContentsMargins(40, 40, 40, 40);

    setStyleSheet("background-color: #101820;");
    UpdateDifficultyButtonStyles();
}

static QString DifficultyToString(GameDifficulty difficulty)
{
    switch (difficulty)
    {
    case GameDifficulty::Easy:
        return QStringLiteral("Easy");
    case GameDifficulty::Normal:
        return QStringLiteral("Normal");
    case GameDifficulty::Hard:
        return QStringLiteral("Hard");
    }

    return QStringLiteral("Normal");
}

void MainMenuWidget::UpdateDifficultyButtonStyles()
{
    m_easyButton->setStyleSheet(m_selectedDifficulty == GameDifficulty::Easy ? activeStyle : inactiveStyle);
    m_normalButton->setStyleSheet(m_selectedDifficulty == GameDifficulty::Normal ? activeStyle : inactiveStyle);
    m_hardButton->setStyleSheet(m_selectedDifficulty == GameDifficulty::Hard ? activeStyle : inactiveStyle);
    m_difficultyButton->setText(QStringLiteral("Difficulty: %1").arg(DifficultyToString(m_selectedDifficulty)));
}
