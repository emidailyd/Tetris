#include "HighscoreWidget.h"
#include "HighscoreManager.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>

HighscoreWidget::HighscoreWidget(HighscoreManager *manager, QWidget *parent)
    : QWidget(parent), m_manager(manager)
{
    QLabel *titleLabel = new QLabel("Highscores", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: white;");

    m_scoreList = new QListWidget(this);
    m_scoreList->setStyleSheet("QListWidget { background-color: #121b28; color: white; border: 1px solid #3a4b62; }"
                               "QListWidget::item:selected { background-color: #64b4ff; color: #101820; }");

    m_backButton = new QPushButton("Back", this);
    m_backButton->setFixedHeight(36);
    m_backButton->setFocusPolicy(Qt::NoFocus);
    connect(m_backButton, &QPushButton::clicked, this, &HighscoreWidget::BackRequested);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(16);
    layout->addWidget(titleLabel);
    layout->addWidget(m_scoreList, 1);
    layout->addWidget(m_backButton);
    layout->setContentsMargins(40, 40, 40, 40);

    setStyleSheet("background-color: #101820;");
}

void HighscoreWidget::UpdateDisplay(const std::vector<int> &highscores)
{
    m_scoreList->clear();
    if (highscores.empty())
    {
        m_scoreList->addItem("No highscores yet.");
        return;
    }

    int rank = 1;
    for (int score : highscores)
    {
        m_scoreList->addItem(QStringLiteral("%1. %2").arg(rank).arg(score));
        ++rank;
    }
}
