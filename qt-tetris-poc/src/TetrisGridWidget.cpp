#include "TetrisGridWidget.h"

#include <QPainter>
#include <QPaintEvent>
#include <QPen>
#include <QRandomGenerator>

TetrisGridWidget::TetrisGridWidget(QWidget* parent)
    : QWidget(parent)
{
    setWindowTitle("Qt Tetris PoC");
    setFixedSize(kColumns * kCellSize, kRows * kCellSize);

    m_fallTimer.setInterval(280);
    connect(&m_fallTimer, &QTimer::timeout, this, &TetrisGridWidget::advanceBlock);
    m_fallTimer.start();
}

void TetrisGridWidget::paintEvent(QPaintEvent* event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, false);

    painter.fillRect(rect(), QColor(18, 26, 38));

    QPen gridPen(QColor(62, 78, 96));
    gridPen.setWidth(1);
    painter.setPen(gridPen);

    for (int column = 0; column <= kColumns; ++column) {
        const int x = column * kCellSize;
        painter.drawLine(x, 0, x, height());
    }

    for (int row = 0; row <= kRows; ++row) {
        const int y = row * kCellSize;
        painter.drawLine(0, y, width(), y);
    }

    const QRect blockRect(
        m_blockColumn * kCellSize,
        m_blockRow * kCellSize,
        kCellSize,
        kCellSize);

    painter.fillRect(blockRect.adjusted(2, 2, -2, -2), QColor(255, 146, 61));
    painter.setPen(QPen(QColor(255, 214, 153), 2));
    painter.drawRect(blockRect.adjusted(1, 1, -1, -1));

    event->accept();
}

void TetrisGridWidget::advanceBlock()
{
    ++m_blockRow;
    if (m_blockRow >= kRows) {
        m_blockRow = 0;
        m_blockColumn = QRandomGenerator::global()->bounded(kColumns);
    }

    update();
}
