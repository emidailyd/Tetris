#pragma once

#include <QWidget>

#include "TetrisController.h"
#include "TetrisRenderer.h"

class QKeyEvent;
class QPaintEvent;

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
    TetrisRenderer m_renderer;
    TetrisController m_controller;

    static constexpr int kColumns = 10;
    static constexpr int kRows = 20;
    static constexpr int kCellSize = 28;
};
