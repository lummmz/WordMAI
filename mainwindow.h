#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "PTextEdit.h"

#include <QLabel>
#include <QMainWindow>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QToolBar>
#include <QVBoxLayout>
#include <QVector>

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    //куча приватных переменных и методов(но их надо дополнять и как-то сортировать)
    QToolBar *createToolbar();
    QToolBar *toolbar;
    QVector<QString> *fileText;
    QVBoxLayout *layout;
    QPushButton *pushButton;
    PTextEdit *textEdit;
    QLabel *TextLabel;

    void setupLayout();
    void readTextFromFile(QString filename);
    void findString(QString string);
public:
    //Публичная вещь, конструктор и деструктор
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    //Те самые слоты, которые нужны для action в этом случае публичные
    void placeHeader();
    void placeText();
    void placeImage();
    void printCheck();
    void normalizeText();
    void liveEdit();
    void placeCurs();
    void placeBold();
    void placeStrike();
    void placeHR();
    void increaseSize();
protected:
    //Надо в private перенести
    void toolbarToLeft();
};
#endif // MAINWINDOW_H
