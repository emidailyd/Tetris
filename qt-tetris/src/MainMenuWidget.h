#pragma once

#include <QWidget>
#include "model/GameSettings.h"

class QPushButton;
class QLabel;

class MainMenuWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenuWidget(QWidget *parent = nullptr);

signals:
    void StartGameRequested(GameDifficulty difficulty);
    void HighscoresRequested();
    void ExitRequested();

private:
    void UpdateDifficultyButtonStyles();

    QLabel *m_titleLabel = nullptr;
    QPushButton *m_difficultyButton = nullptr;
    QWidget *m_difficultyOptionsWidget = nullptr;
    QPushButton *m_easyButton = nullptr;
    QPushButton *m_normalButton = nullptr;
    QPushButton *m_hardButton = nullptr;
    QPushButton *m_startButton = nullptr;
    QPushButton *m_highscoreButton = nullptr;
    QPushButton *m_exitButton = nullptr;
    GameDifficulty m_selectedDifficulty = GameDifficulty::Normal;
};
