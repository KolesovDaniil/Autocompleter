#include "typechoose.h"
#include "ui_typechoose.h"

typeChoose::typeChoose(QWidget* parent, Trie<QString, type>* _trie, QString _str):
    QDialog(parent),
    ui(new Ui::typeChoose),
    str(_str),
    trie(_trie)
{
    ui->setupUi(this);
}

typeChoose::~typeChoose()
{
    delete ui;
}

void typeChoose::on_pushButton_2_clicked()
{
    int index = ui->comboBox->currentIndex();
    switch (index) {
    case 0:
        trie->add(str, FUNC);
        break;
    case 1:
        trie->add(str, CONST);
        break;
    case 2:
        trie->add(str, SERV_WORD);
        break;
    }
    this->close();
}

void typeChoose::on_pushButton_clicked()
{
    this->close();
}
