#pragma once

#include <QDialog>
#include <trie.h>

namespace Ui {
class typeChoose;
}

class typeChoose : public QDialog
{
    Q_OBJECT

public:
    typeChoose(QWidget*, Trie<QString, type>*, QString);
    ~typeChoose();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::typeChoose *ui;
    QString str;
    Trie<QString, type>* trie;
};
