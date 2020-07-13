#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QToolBar>
#include <QVBoxLayout>
#include <QVector>

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QToolBar *createToolbar();
    QToolBar *toolbar;
    QVector<QString> *poeshGovna;
    QVBoxLayout *layout;
    QPushButton *pushButton;
    QTextEdit *textEdit;
    QLabel *TextLabel;

    void setupLayout();
    void readTextFromFuckingFile(QString filename);
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
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
    void toolbarToLeft();
};
#endif // MAINWINDOW_H
