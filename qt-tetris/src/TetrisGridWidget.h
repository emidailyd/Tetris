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

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void OnGameUpdated();

private:
    void ConfigureSettingsButtons();
    void SelectDifficulty(GameDifficulty difficulty);
    void UpdateDifficultyButtonStyles();

    TetrisRenderer m_renderer;
    TetrisController m_controller;
    QPushButton *m_easyButton = nullptr;
    QPushButton *m_normalButton = nullptr;
    QPushButton *m_hardButton = nullptr;
};
