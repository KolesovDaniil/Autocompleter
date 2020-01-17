#pragma once
#include <map>
#include <QChar>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QTextStream>
#include <QFileDialog>
template<class Key, class Value>
class TrieNode
{
bool naveChildren(){
    if(map.cbegin() != map.cend())
        return true;
    else return false;
}
public:
    static void deleteNode(TrieNode<QChar,Value>*& _node){
        if(_node){
            foreach (auto i, _node->map) {
                deleteNode(i.second);
            }
        }
        delete _node;
        _node = nullptr;
    }
    static QJsonObject trieNodeToJson(TrieNode<Key, Value>* _node);

    static QJsonObject mapToJson(TrieNode<Key, Value>* _node);

    bool isWord;

    std::map<Key, TrieNode*> map;

    Value value;

    TrieNode(): isWord(false), map(), value() {}

    TrieNode(bool _isWord, Value _value): isWord(_isWord), map(), value(_value) {}

    static TrieNode<QChar,Value>* fromJsonToNode(QJsonObject jObj, int& count){
        int _type = jObj.value("value").toInt();
        TrieNode<QChar,Value>* trieNodePtr = new TrieNode<QChar,Value>;
        trieNodePtr->isWord = jObj.value("isWord").toBool();
        if(trieNodePtr->isWord){
            count++;
        }
        switch (_type) {
        case 0:
            trieNodePtr->value = static_cast<Value>(0);
            break;
        case 1:
            trieNodePtr->value = static_cast<Value>(1);
            break;
        case 2:
            trieNodePtr->value = static_cast<Value>(2);
            break;
        }
        jObj = jObj.value("map").toObject();
        foreach (auto i, jObj.keys()) {
            trieNodePtr->map[i[0]] = fromJsonToNode(jObj.value(i).toObject(), count);
        }
        return trieNodePtr;
    }
};
template<class Key,class Value>
QJsonObject TrieNode<Key, Value>::trieNodeToJson(TrieNode<Key,Value>* _node){
    QJsonObject jObj;
    jObj.insert("isWord", QJsonValue::fromVariant(_node->isWord));
    jObj.insert("value", QJsonValue::fromVariant(_node->value));
    jObj.insert("map", mapToJson(_node));
    return jObj;
}

template<class Key,class Value>
QJsonObject TrieNode<Key, Value>::mapToJson(TrieNode<Key,Value>* _node){
    QJsonObject jObj;
    foreach (auto i, _node->map) {
        jObj.insert(QString(i.first), trieNodeToJson(i.second));
    }
    return jObj;
}
