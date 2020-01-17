#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <trie.h>
#include "typechoose.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_lineEdit_cursorPositionChanged(int arg1, int arg2);

    void on_actionSave_triggered();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_actionOpen_triggered();

private:
    Trie<QString, type> trie;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
