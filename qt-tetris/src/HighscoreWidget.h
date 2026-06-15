#pragma once

#include <QWidget>
#include <vector>

class HighscoreManager;
class QListWidget;
class QPushButton;

class HighscoreWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HighscoreWidget(HighscoreManager *manager, QWidget *parent = nullptr);

    void UpdateDisplay(const std::vector<int> &highscores);

signals:
    void BackRequested();

private:
    HighscoreManager *m_manager = nullptr;
    QListWidget *m_scoreList = nullptr;
    QPushButton *m_backButton = nullptr;
};
