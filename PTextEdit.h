#ifndef PTEXTEDIT_H
#define PTEXTEDIT_H

#include <QTextEdit>


class PTextEdit : public QTextEdit {
public:
    PTextEdit(QWidget *parent = nullptr);

    bool event(QEvent *e);

};

#endif // PTEXTEDIT_H
