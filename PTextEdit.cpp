#include "PTextEdit.h"

#include <QDir>
#include <QInputDialog>
#include <QTextStream>

PTextEdit::PTextEdit(QWidget *parent) {
    fileLines = new QVector<QString>;
    setMouseTracking(true);
}
void PTextEdit::saveFile() {
    QString text = toHtml();
    fileName = QInputDialog::getText(this, tr("File Name"), tr("Name"), QLineEdit::Normal, QDir::home().dirName(),&ok);
    if(ok && !fileName.isEmpty()) {
        QFile file(fileName + ".lect");
        if(file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream stream(&file);
            stream << text;
    }
    }
}
