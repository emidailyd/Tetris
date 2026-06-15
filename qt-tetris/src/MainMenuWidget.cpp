#include "MainMenuWidget.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

MainMenuWidget::MainMenuWidget(QWidget *parent)
    : QWidget(parent)
{
    m_titleLabel = new QLabel("Qt Tetris", this);
    m_titleLabel->setAlignment(Qt::AlignCenter);
    m_titleLabel->setStyleSheet("font-size: 32px; font-weight: bold; color: white;");

    m_startButton = new QPushButton("Start Game", this);
    m_highscoreButton = new QPushButton("Highscores", this);
    m_exitButton = new QPushButton("Exit", this);

    m_startButton->setFixedHeight(40);
    m_highscoreButton->setFixedHeight(40);
    m_exitButton->setFixedHeight(40);

    m_startButton->setFocusPolicy(Qt::NoFocus);
    m_highscoreButton->setFocusPolicy(Qt::NoFocus);
    m_exitButton->setFocusPolicy(Qt::NoFocus);

    connect(m_startButton, &QPushButton::clicked, this, &MainMenuWidget::StartGameRequested);
    connect(m_highscoreButton, &QPushButton::clicked, this, &MainMenuWidget::HighscoresRequested);
    connect(m_exitButton, &QPushButton::clicked, this, &MainMenuWidget::ExitRequested);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(16);
    layout->addWidget(m_titleLabel);
    layout->addSpacing(24);
    layout->addWidget(m_startButton);
    layout->addWidget(m_highscoreButton);
    layout->addWidget(m_exitButton);
    layout->setContentsMargins(40, 40, 40, 40);

    setStyleSheet("background-color: #101820;");
}
