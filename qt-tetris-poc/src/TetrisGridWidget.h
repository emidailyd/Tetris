#pragma once

#include <QTimer>
#include <QWidget>

class TetrisGridWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TetrisGridWidget(QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;

private slots:
    void advanceBlock();

private:
    static constexpr int kColumns = 10;
    static constexpr int kRows = 20;
    static constexpr int kCellSize = 28;

    QTimer m_fallTimer;
    int m_blockColumn = kColumns / 2;
    int m_blockRow = 0;
};
