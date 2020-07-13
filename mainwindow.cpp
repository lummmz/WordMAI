#include "mainwindow.h"

#include <QVBoxLayout>
#include <QAction>
#include <QDebug>
#include <QFileDialog>
#include <QVector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    addToolBar(createToolbar());
    toolbarToLeft();
    setupLayout();
    poeshGovna = new QVector<QString>();
}

MainWindow::~MainWindow(){ delete pushButton;  };

void MainWindow::toolbarToLeft() {
    removeToolBar(this->toolbar);
    addToolBar(Qt::LeftToolBarArea, this->toolbar);
    this->toolbar->show();
}

QToolBar *MainWindow::createToolbar() {
    this->toolbar = new QToolBar();
    QAction *quitAction = new QAction("&Open File",this);
    QAction *setTextAction = new QAction("&Read Text from file", this);
    QAction *addImage = new QAction("Add Image", this);
    QAction *makeHeader = new QAction("Create Header", this);
    QAction *normalizeText = new QAction("Normalize", this);
    QAction *liveEditMode = new QAction("Live Edit", this);
    QAction *cursiveText = new QAction("Cursive", this);
    QAction *boldText = new QAction("Bold", this);
    QAction *strikeText = new QAction("Strike", this);
    QAction *makeHR = new QAction("HR", this);
    QAction *increaseFont = new QAction("+", this);
    connect(addImage, SIGNAL(triggered()), SLOT(placeImage()));
    connect(quitAction, SIGNAL(triggered()), SLOT(printCheck()));
    connect(setTextAction, SIGNAL(triggered()), SLOT(placeText()));
    connect(makeHeader, SIGNAL(triggered()), SLOT(placeHeader()));
    connect(normalizeText, SIGNAL(triggered()), SLOT(normalizeText()));
    connect(liveEditMode, SIGNAL(triggered()), SLOT(liveEdit()));
    connect(cursiveText, SIGNAL(triggered()), SLOT(placeCurs()));
    connect(boldText, SIGNAL(triggered()), SLOT(placeBold()));
    connect(strikeText, SIGNAL(triggered()), SLOT(placeStrike()));
    connect(makeHR, SIGNAL(triggered()), SLOT(placeHR()));
    connect(increaseFont, SIGNAL(triggered()), SLOT(increaseSize()));
    this->toolbar->addAction(quitAction);
    this->toolbar->addAction(setTextAction);
    this->toolbar->addAction(addImage);
    this->toolbar->addAction(makeHeader);
    this->toolbar->addAction(normalizeText);
    this->toolbar->addAction(liveEditMode);
    this->toolbar->addAction(cursiveText);
    this->toolbar->addAction(boldText);
    this->toolbar->addAction(strikeText);
    this->toolbar->addAction(makeHR);
    this->toolbar->addAction(increaseFont);
    return toolbar;
}

void MainWindow::printCheck() {
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this,"Fuck", "", "*.txt") ;
    this->readTextFromFuckingFile(fileName);
}

void MainWindow::liveEdit() {
    if(this->textEdit->isReadOnly()) {
        this->textEdit->setReadOnly(false);
    } else {
        this->textEdit->setReadOnly(true);
    }
}

void MainWindow::readTextFromFuckingFile(QString fileName) {
    qDebug() << fileName;
    QFile file(fileName);
    QTextStream instream (&file);
    if(!file.open(QIODevice::ReadWrite)) {
        qDebug() << "Oshibochka" << file.error();
    }
    while(!instream.atEnd()) {
        this->poeshGovna->push_back(instream.readLine());
        qDebug() << instream.readLine();
}
}

void MainWindow::placeHeader() {
    QTextCursor textCursor = this->textEdit->textCursor();
    if (textCursor.hasSelection()) {
        textCursor.insertHtml("<center><h1>" + textCursor.selectedText() + "</h1>" + "<p>" + "</p>"+"</center>");
    }
}

void MainWindow::normalizeText() {
    QTextCursor textCursor = this->textEdit->textCursor();
    if (textCursor.hasSelection()) {
        textCursor.insertHtml(textCursor.selectedText());
    }
}

void MainWindow::placeImage() {
    QString imageSrc;
    QString htmlImage;
    imageSrc = QFileDialog::getOpenFileName(this, "Fuck", "", "*.png");
    htmlImage = this->textEdit->toHtml() + "<p></p>" + "<center>" +  "<img src =" + imageSrc + ">" + "</img>" + "</center>";
    this->textEdit->setHtml(htmlImage);
}

void MainWindow::placeCurs() {
    QTextCursor textCursor = this->textEdit->textCursor();
    if(textCursor.hasSelection()) {
        textCursor.insertHtml("<i>" + textCursor.selectedText() + "</i>");
    }
}

void MainWindow::placeBold() {
    QTextCursor textCursor = this->textEdit->textCursor();
    if(textCursor.hasSelection()) {
        textCursor.insertHtml("<b>" + textCursor.selectedText() + "</b>");
    }
}

void MainWindow::placeStrike() {
    QTextCursor textCursor = this->textEdit->textCursor();
    if(textCursor.hasSelection()){
        textCursor.insertHtml("<strike>" + textCursor.selectedText() + "</strike>");
    }
}
void MainWindow::placeHR() {
    QTextCursor textCursor = this->textEdit->textCursor();
        textCursor.insertHtml("<hr>" + textCursor.selectedText() + "</hr>");
}

void MainWindow::placeText() {
    for(int i = 0; i < this->poeshGovna->size(); i++) {
        QString line = this->poeshGovna->value(i);
        qDebug() << line;
        this->textEdit->append(line);
    }
}

void MainWindow::increaseSize() {
QTextCursor cursor = this->textEdit->textCursor();
this->textEdit->selectAll();
this->textEdit->setFontPointSize(14);
this->textEdit->setTextCursor(cursor);
}
void MainWindow::setupLayout() {
    QWidget *central = new QWidget();
    textEdit = new QTextEdit();
    this->textEdit->setReadOnly(true);
    this->layout = new QVBoxLayout();
    this->layout->addWidget(this->textEdit);
    central->setLayout(this->layout);
    setCentralWidget(central);
}
