#include <QApplication>
#include <QSurfaceFormat>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Set the window up
    MainWindow window;
    window.show();
    return app.exec();
}
