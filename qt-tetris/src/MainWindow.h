#pragma once

#include <QMainWindow>

class MainMenuWidget;
class TetrisGridWidget;
class HighscoreWidget;
class HighscoreManager;
class QStackedWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void ShowMainMenu();
    void StartNewGame();
    void ShowHighscores();
    void HandleGameOver(int finalScore);
    void OnExitRequested();

private:
    QStackedWidget *m_stack = nullptr;
    MainMenuWidget *m_mainMenu = nullptr;
    TetrisGridWidget *m_gameWidget = nullptr;
    HighscoreWidget *m_highscoreWidget = nullptr;
    HighscoreManager *m_highscoreManager = nullptr;
};
