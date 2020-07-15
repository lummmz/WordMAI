#include "mainwindow.h"

#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow *mainWindow = new MainWindow();
    mainWindow->showMaximized();
    return a.exec();
}
