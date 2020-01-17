#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , trie()
{
    ui->setupUi(this);
    trie.readFile("start.json");
    QMap<QString, type> map = trie.trieToMapFromStart();
    foreach (auto i, map.keys()) {
        type tp = map[i];
        switch (tp) {
        case CONST:
            ui->listWidget->insertItem(ui->listWidget->currentRow(), i + " : CONST");
            break;
        case FUNC:
            ui->listWidget->insertItem(ui->listWidget->currentRow(), i + " : FUNC");
            break;
        case SERV_WORD:
            ui->listWidget->insertItem(ui->listWidget->currentRow(), i + " : SERV_WORD");
            break;
        }
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_lineEdit_cursorPositionChanged(int arg1, int arg2)
{
    ui->listWidget->clear();
    QString str = ui->lineEdit->text();
    QMap<QString, type> map = trie.trieToMapFromStart();
    QStringList lst = trie.keys(str);
    foreach (auto i, lst) {
        type tp = map[str+i];
        switch (tp) {
        case FUNC:
            ui->listWidget->insertItem(ui->listWidget->currentRow(), str+i+" : FUNC");
            break;
        case CONST:
            ui->listWidget->insertItem(ui->listWidget->currentRow(), str+i+" : CONST");
            break;
        case SERV_WORD:
            ui->listWidget->insertItem(ui->listWidget->currentRow(), str+i+" : SERV_WORD");
            break;
        }
    }
}

void MainWindow::on_actionSave_triggered()
{
    QString fileName=
            QFileDialog::getSaveFileName( this,
                                          tr("Сохранить файл как"),
                                          "new",
                                          tr("JSON(*.json)")
                                          );
    // Если указали путь, сохраняем
    if(!fileName.isEmpty())
    {
        trie.writeFile(fileName);
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    trie.deleteWord(ui->lineEdit->text());
    ui->lineEdit->clear();
}

void MainWindow::on_pushButton_clicked()
{
    typeChoose window(this, &trie, ui->lineEdit->text());
    window.setModal(true);
    window.exec();
    ui->lineEdit->clear();
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName=
            QFileDialog::getOpenFileName(this);
    // Если указали путь, загружаем
    if(!fileName.isEmpty())
    {
        trie.readFile(fileName);
        on_lineEdit_cursorPositionChanged(0, 0);
    }
}
