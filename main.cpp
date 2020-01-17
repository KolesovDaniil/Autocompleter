#include "mainwindow.h"
#include <trie.h>
#include <iostream>
#include <QString>
#include <QTextStream>
#include <QApplication>
#include <assert.h>


int main(int argc, char *argv[])
{
    Trie<QString, type> _trie1;
    Trie<QString, type> _trie2;
    QTextStream Qcout(stdout);
    assert(_trie1.size() == 0);
    _trie1.add("cat", FUNC);
    assert(_trie1.size() == 1);
    _trie1.add("cat", FUNC);
    assert(_trie1.size() == 1);
    assert(_trie1.search("cat") == true);
    assert(_trie1["cat"] == 1);
    _trie1.deleteWord("cat");
    assert(_trie1.size() == 0);
    _trie1.deleteWord("cat");
    assert(_trie1.size() == 0);
    assert(_trie1.search("cat") == false);
    _trie1.add("cat", FUNC);
    Trie<QString, type> _trie3(_trie1);
    assert(_trie3 == _trie1);
    _trie1.deleteWord("dog");
    _trie1.writeFile("test.json");
    _trie1.deleteWord("dog");
    assert(_trie1 == _trie3);
    _trie1.readFile("test.json");
    _trie1.deleteWord("dog");
    assert(_trie1.size() == 1);
    assert(_trie1.search("dog") == false);
    _trie1.clear();
    assert(_trie1 == _trie2);
    std::cout << "All tests completed!" << std::endl;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
