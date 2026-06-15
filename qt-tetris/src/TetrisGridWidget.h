#pragma once

#include <QWidget>

#include "TetrisController.h"
#include "TetrisRenderer.h"

class QKeyEvent;
class QPaintEvent;
class QPushButton;

class TetrisGridWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TetrisGridWidget(QWidget *parent = nullptr);

    void StartGame();
    void SetDifficulty(GameDifficulty difficulty);

signals:
    void GameOver(int finalScore);

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void OnGameUpdated();
    void OnGameOver(int finalScore);

private:
    TetrisRenderer m_renderer;
    TetrisController m_controller;
};
