#ifndef PTEXTEDIT_H
#define PTEXTEDIT_H

#include <QTextEdit>


class PTextEdit : public QTextEdit {
private:
    bool ok;
    QString fileName;
    QVector<QString> *fileLines;

public:
    PTextEdit(QWidget *parent = nullptr);

    bool event(QEvent *e);
public slots:
    void saveFile();
};

#endif // PTEXTEDIT_H
