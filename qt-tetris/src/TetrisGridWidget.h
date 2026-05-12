#pragma once

#include <QTimer>
#include <QWidget>

#include "model/GameState.h"

class QKeyEvent;

class TetrisGridWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TetrisGridWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void advanceGame();

private:
    void resetGame();
    void drawCell(QPainter &painter, int row, int column, const QColor &fillColor) const;

    static constexpr int kColumns = 10;
    static constexpr int kRows = 20;
    static constexpr int kCellSize = 28;

    QTimer m_fallTimer;
    GameState m_gameState;
};
