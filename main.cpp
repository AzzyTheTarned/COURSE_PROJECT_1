#include "mainwindow.h"

#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow main_window;
    main_window.setFixedHeight(863);
    main_window.setFixedWidth(800);
    main_window.show();
    return a.exec();
}
