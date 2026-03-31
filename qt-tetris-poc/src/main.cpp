#include <QApplication>

#include "TetrisGridWidget.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    TetrisGridWidget widget;
    widget.show();

    return app.exec();
}
