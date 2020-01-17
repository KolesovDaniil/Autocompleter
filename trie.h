#pragma once
#include <iostream>
#include <trienode.h>
#include <QFile>
#include <QVector>
#include <QMap>
#include <QTextStream>

enum type {CONST, FUNC, SERV_WORD};

template <class Key, class Value>
class Trie{
private:
    QMap<QString, Value> trieToMap(TrieNode<QChar,Value>* ptr){
        QMap<QString, Value> map;
        QString qstr;
        if(ptr != nullptr){
            map = writeMap(ptr, qstr);
        }
        return map;
    }
    QMap<QString, Value> writeMap(TrieNode<QChar,Value>* _node, QString i_str){
        QMap<QString, Value> map;
        if(_node->isWord){
            map[i_str] = _node->value;
        }
        foreach (auto i, _node->map) {
            QMap<QString, Value> map2 = writeMap(i.second, i_str + i.first);
            foreach (auto i, map2.keys()) {
                map[i] = map2[i];
            }
        }
        return map;
    }

    TrieNode<QChar,Value>* nodeSearch(Key str){
        TrieNode<QChar,Value>* curr = root;
        if(curr == nullptr) return nullptr;
        for(auto i : str){
            if(curr->map.find(i) != curr->map.end()){
                curr = curr->map[i];
            }
            else return nullptr;
        }
        return curr;
    }
    bool partDelete(Key& str, TrieNode<QChar,Value>* ptr){
        if (ptr == nullptr)
            return false;
        if (str.size() == 0) {
            if (ptr->isWord == true) {
                ptr->isWord = false;
                return true;
            }
            return false;
        }

        Key part = str.right(str.size() - 1);

        if (this->partDelete(part, ptr->map[str[0]])) {
            if (ptr->map[str[0]] == nullptr){
                delete ptr->map[str[0]];
                ptr->map[str[0]] = nullptr;
                return true;
            }
            else return true;
        }
        else return false;
        return false;
    }

    TrieNode<QChar,Value>* root;
    int count;

public:
    QMap<QString, Value> trieToMapFromStart(){
        QMap<QString, Value> map;
        QString qstr;
        if(root != nullptr){
            TrieNode<QChar,Value>* curr = root;
            map = trieToMap(curr);
        }
        return map;
    }
    Trie(): root(nullptr), count(0) {}
    Trie(Trie& trie): Trie() {
        QMap<QString, Value> map = trie.trieToMapFromStart();
        foreach (auto i, map.keys()) {
            add(i, map[i]);
        }
    }
    ~Trie(){
       clear();
    }
    void clear(){
        TrieNode<QChar,Value>::deleteNode(root);
        count = 0;
    }
    int size(){
        return count;
    }
    void readFile(QString fileName){
        QFile jsonFile(fileName);
        jsonFile.open(QFile::ReadOnly);
        QJsonDocument jDoc = QJsonDocument().fromJson(jsonFile.readAll());
        QString strJson(jDoc.toJson(QJsonDocument::Compact));
        QJsonObject jObj= jDoc.object();
        this->clear();
        root = TrieNode<QChar,Value>::fromJsonToNode(jObj,count);
        jsonFile.close();
    }
    void writeFile(QString fileName){
        QJsonDocument jDoc;
        jDoc.setObject(TrieNode<QChar,Value>::trieNodeToJson(root));
        QFile _file(fileName);
        _file.open(QIODevice::WriteOnly);
        _file.write(jDoc.toJson());
        _file.close();
    }

    bool operator==(Trie& trie){
        if(this->trieToMapFromStart() == trie.trieToMapFromStart()){
            return true;
        }
        else return false;
    }
    void add(Key str, Value value){
        if(root == nullptr){
            root = new TrieNode<QChar,Value>;
        }
        TrieNode<QChar,Value>* curr = root;
        for(auto i : str){
            if(curr->map.find(i) == curr->map.end()){
                curr->map[i] = new TrieNode<QChar,Value>;
            }
            curr = curr->map[i];
        }
        if(!curr->isWord){
            count++;
        }
        curr->isWord = true;
        curr->value = value;
    }

    bool deleteWord(Key str){
        if(search(str)){
            if(partDelete(str, root)){
                count--;
                return true;
            }
            else return false;
        }
        else return false;
    }

    bool search(Key str){
        TrieNode<QChar, Value>* curr = nodeSearch(str);
        if(curr){
            return curr->isWord;
        }
        else return false;
    }

    Value& operator[](Key str){
        TrieNode<QChar, Value>* curr = nodeSearch(str);
        if(curr){
            return curr->value;
        }
        else throw "emptyTrie";
    }

    QList<Key> keys(Key str){
        QList<Key> lst;
        TrieNode<QChar, Value>* curr = nodeSearch(str);
        lst = trieToMap(curr).keys();
        return lst;
    }
};
