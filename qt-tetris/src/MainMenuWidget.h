#pragma once

#include <QWidget>

class QPushButton;
class QLabel;

class MainMenuWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenuWidget(QWidget *parent = nullptr);

signals:
    void StartGameRequested();
    void HighscoresRequested();
    void ExitRequested();

private:
    QLabel *m_titleLabel = nullptr;
    QPushButton *m_startButton = nullptr;
    QPushButton *m_highscoreButton = nullptr;
    QPushButton *m_exitButton = nullptr;
};
