//Импорты заголовочных файлов
#include "PTextEdit.h"
#include "mainwindow.h"
// Импорты библиотек Qt
#include <QVBoxLayout>
#include <QAction>
#include <QDebug>
#include <QFileDialog>
#include <QVector>
#include <QToolTip>
//Конструктор класса MainWindow(объявлен в mainwindow.h)
//TODO: вынести большую част в TODO:
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //в функцию отвечающей за добавление tollbar(менюха слева), передаётся результат функции creaеteToolbar(), которым является объект класса QToolbar(на самом деле указатель на объект, но это не столь важно)
    addToolBar(createToolbar());
    //Функция отвечающая за перемещение toolbar с верхней части окна в левую(надо вынести вот это в layout файлы(сделать адекватный дизайн программы))
    toolbarToLeft();
    //Ещё одна функция которой здесь не должно быть, потому что её надо вынести в ui, она отвечает за установку главного layout(разметки) на окно
    setupLayout();
    //Массив(динамический(не имеет чётких границ, т.е размерность меняется по ходу выполнения программы)) название которого надо поменять, но для этого надо найти все его использования, он нужен для хранения строк при чтении из файла
    fileText = new QVector<QString>();
}
//Деструктор, тоже надо написать
MainWindow::~MainWindow(){ delete pushButton;  };
//Функция переносящая toolbar в левую часть, потому что я решил что так солиднее, но возможно это бред
void MainWindow::toolbarToLeft() {
    //Функция отвечающая за удаление toolbar с верхней части окна
    removeToolBar(this->toolbar);
    //Добавление toolbar на левую часть окна(в качестве аргументов передаётся позиция(Qt::LeftToolBarArea), и ссылка на toolbar, который принадлжеит объекту(подробнее написано в теме про this) вот сейчас думаю и понимаю что это можно было вынести в функцию createToolbar, бывает
    addToolBar(Qt::LeftToolBarArea, this->toolbar);
    //Показать тулбар
    this->toolbar->show();
}
//Самая масштабная пока функция, которая отвечат за добавление всего функционала на тулбар(вот это точно надо переделывать и добавлять в контекстное меню(по правому клику мыши чтобы появлялось))
QToolBar *MainWindow::createToolbar() {
    //Создание объекта класса toolbar, переменная объявлена в mainwindow.h(this надо убирать)
    //Ниже под действиями я обозначаю QAction
    this->toolbar = new QToolBar();
    //Весь блок содержащий в себе QAction, т.е с 38 по 48 строчку отвечает за создние *действия* для тулбара, в качестве аргумента передаётся строка в которой указано имя действие(название которое должно показаться) и указатель на текущи объект(снова this)
    QAction *quitAction = new QAction("Open File",this);
    QAction *setTextAction = new QAction("Read Text from file", this);
    QAction *addImage = new QAction("Add Image", this);
    QAction *makeHeader = new QAction("Create Header", this);
    QAction *normalizeText = new QAction("Normalize", this);
    QAction *liveEditMode = new QAction("Live Edit", this);
    QAction *cursiveText = new QAction("Cursive", this);
    QAction *boldText = new QAction("Bold", this);
    QAction *strikeText = new QAction("Strike", this);
    QAction *makeHR = new QAction("HR", this);
    QAction *increaseFont = new QAction("+", this);
    //Ниже идёт блок(50-60 строки) отвечающий за добавление логики к действиям(что будет происходить когда на кнопку тыкнешь), в качестве аргументов передаётся действие, они объявлены выше, потом передаётся SIGNALS(сигналы(какое конкретно действие должно произойти, чтобы кнопка сработала)), и SLOTS(слоты(что должно произойти(сам пока не очень разобрался как работает, может есть реализация получше моей))
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
    //Ниже идёт блок, который отвечает за добавление созданных действий на тулбар, тут всё просто, передаём функции действия
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
//Бесплолезная функция которую можно удалять
void MainWindow::printCheck() {
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this,"Fuck", "", "*.txt") ;
    this->readTextFromFile(fileName);
}
//Функция которая отвечает за возможность редактирования текста(TextEdit, это ниже объявлено//Функция которая отвечает за возможность редактирования текста(TextEdit, это ниже объявлено), название тоже надо поменять
void MainWindow::liveEdit() {
    //Проверка можно ли редактировать текст сейчас
    if(this->textEdit->isReadOnly()) {
        //если да, то мы передаём то что textedit больше не readonly
        this->textEdit->setReadOnly(false);
    } else {
        //если текст нельзя редактировать, то мы разрешаем его редактировать
        this->textEdit->setReadOnly(true);
    }
    //Это всё нужно, чтобы когда мы тыкаем на кнопку, у нас textedit менял своё состояние в зависимости от текущего состояния(если можно редактировать, то он запрещает и наоборот)
}
//Очередная функция название которой надо поменять она отвечает за чтение строк из файла
void MainWindow::readTextFromFile(QString fileName) {
    //дебаг, типо cout(print()) но в qt
    qDebug() << fileName;
    //Создание объекта класса file, которому передаётся имя файла
    QFile file(fileName);
    //Создание потока вывод(сложная тема, что-то типо cout, за подробностями в гугл)
    QTextStream instream (&file);
    //Файл открывается в возможности просмотра и только и если он вернул ошибку, то она напечатается
    if(!file.open(QIODevice::ReadWrite)) {
        qDebug() << "Oshibochka" << file.error();
    }
    //Пока поток не дошёл до конца(обычный цикл while)
    while(!instream.atEnd()) {
        //В массив добавляется строчки, прочитанные из файла
        this->fileText->push_back(instream.readLine());
        //На всякий случай в консоль вывожу, обязательно убрать в релизе
        qDebug() << instream.readLine();
    }
}
//Дальше идут самые основные функции, они созданы чтобы редактировать текст, всё редактирование идёт через html(язык разметки, на нём сайтики делаются)
void MainWindow::placeHeader() {
    //Создаётся объект класса QTextCursor который представляет собой курсор
    QTextCursor textCursor = this->textEdit->textCursor();
    //Если что-то выделено - то...
    if (textCursor.hasSelection()) {
        //Заместо курсора пихается html код в данном случае текст становится заголовком
        textCursor.insertHtml("<center><h1>" + textCursor.selectedText() + "</h1>" + "<p>" + "</p>"+"</center>");
    }
}
//Костыльная функция которую надо передлать/убрать, она отвечает за возвращение текста к исходному состоянию, работает правильно, но по идее не должна
void MainWindow::normalizeText() {
    QTextCursor textCursor = this->textEdit->textCursor();
    if (textCursor.hasSelection()) {
        textCursor.insertHtml(textCursor.selectedText());
    }
}
//В текст пихается картинка, это тоже делается через html теги, но здесь всё сложнее
void MainWindow::placeImage() {
    QString imageSrc;
    QString htmlImage;
    //Создаётся диалоговое окно с выбором файла(только png(тоже надо переделать)), дальше когда пользователь выбирает картинку программа получает полный путь до неё
    imageSrc = QFileDialog::getOpenFileName(this, "Fuck", "", "*.png");
    //Ну это я решил удариться в правильно написание и строки в отдельную переменную по хорошему так везде надо сделать, здсь через html теги добавляется картинки
    htmlImage = this->textEdit->toHtml() + "<p></p>" + "<center>" +  "<img src =" + imageSrc + ">" + "</img>" + "</center>";
    this->textEdit->setHtml(htmlImage);
}
//Работает так же как и placeHeader, только делает курсив
void MainWindow::placeCurs() {
    QTextCursor textCursor = this->textEdit->textCursor();
    if(textCursor.hasSelection()) {
        textCursor.insertHtml("<i>" + textCursor.selectedText() + "</i>");
    }
}
//Работает так же как и placeHeader, только делает жирный тектс
void MainWindow::placeBold() {
    QTextCursor textCursor = this->textEdit->textCursor();
    if(textCursor.hasSelection()) {
        textCursor.insertHtml("<b>" + textCursor.selectedText() + "</b>");
    }
}
//Не работает, надо переделать или починить
void MainWindow::placeStrike() {
    QTextCursor textCursor = this->textEdit->textCursor();
    if(textCursor.hasSelection()){
        textCursor.insertHtml("<strike>" + textCursor.selectedText() + "</strike>");
    }
}
//работает так же как и placeHeader, только делает полосу(проще увидеть что это чем понять)
void MainWindow::placeHR() {
    QTextCursor textCursor = this->textEdit->textCursor();
    textCursor.insertHtml("<hr>" + textCursor.selectedText() + "</hr>");
}
//Функция которая пихает текст в textedit(на экран его выводит)
void MainWindow::placeText() {
    //Цикл по массиву, как и везде
    for(int i = 0; i < this->fileText->size(); i++) {
        //Вот это бред какой-то, оно короче не так должно работать, но я сделал так. Во временную переменную сохраняется строка, содержащая в себе строку текста
        //Не ну красный текст надо убрать конечно
        QString line = "<font color=\"red\">" + this->fileText->value(i) + "</font>";
        //Выводится в консоль в релизе не должно быть
        qDebug() << line;
        //Само добавление строки
        this->textEdit->insertHtml(line);
    }
}
//Увеличение размера текста(ЛЮТЫЙ КОСТЫЛЬ, ПРОСТО СРОЧНО УБИРАТЬ)
void MainWindow::increaseSize() {
    QTextCursor cursor = this->textEdit->textCursor();
    this->textEdit->selectAll();
    this->textEdit->setFontPointSize(14);
    this->textEdit->setTextCursor(cursor);
}
//вообще жесть короче, я переопределяю функцию event
bool PTextEdit::event(QEvent *event) {
    if(event->type() == QEvent::ToolTip) {
        //Конвертация вспомогательного ивента к обычному ивенту(нашёл на стаке)
        QHelpEvent *helpEvent = static_cast<QHelpEvent*>(event);
        //Курсор для текста
        QTextCursor cursor = textCursor();
        //А вот это убрать надо в релизе
        qDebug() << cursor.selectedText();
        if(!cursor.selectedText().isEmpty()) {
            //Если строка совпадает с нужной мне(потом надо будет переписать в отдельную функцию, потому что строк будет много)
            if(cursor.selectedText() == "Lorem ipsum") {
            //Собственно показывается текст
             QToolTip::showText(helpEvent->globalPos(), QString("Jopa"));
            }
        }
        } else {
            QToolTip::hideText();
        }
    return true;
}
PTextEdit::PTextEdit(QWidget *parent):QTextEdit(parent) {
    //обычный конструктор, в котором я включаю отслеживание мышки
    setMouseTracking(true);
}

void MainWindow::findString(QString string) {
    for(int i = 0; i < fileText->size(); i++) {
        //ненавижу это
    }
}

//Создание layout(разметки)
void MainWindow::setupLayout() {
    //UI!=ФАЙЛ .ui
    //Ээээ, тут дальше короче странно идёт, я наверное неправильно сделал, но работает отлично(но переделать надо под UI)
    //Создаётся виджет
    QWidget *central = new QWidget();
    //Создаётся TextEdit(поле для редактирования текста)
    textEdit = new PTextEdit();
    //Делается чтобы нельзя было редактировать
    this->textEdit->setReadOnly(true);
    //Создаётся разметка, тоже this лишнее
    this->layout = new QVBoxLayout();
    //На разметку добавляется виджет
    this->layout->addWidget(this->textEdit);
    //На другой виджет добавляется разметка
    /*Схема такая(дерево)
    1.Виджет(самый короче главный после окна)
    2.Разметка(сидит на виджете)
    3.Виджеты(которые на разметке)
    */
    //Разметка добавляется на виджет
    central->setLayout(this->layout);
    //Виджет становится центральным(главным)
    setCentralWidget(central);
}
