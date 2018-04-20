#ifndef MYTESTA_H
#define MYTESTA_H

#include <QObject>
#include <QVector>
#include <QDebug>

struct Node{
    int a;
    Node() : a(0) {}
    Node(const Node& other) :
    a(other.a)
    {
        qDebug() << "copy constructor";
    }
};


class MyTestA : public QObject
{
    Q_OBJECT
public:
    explicit MyTestA(QObject *parent = nullptr);

signals:
    void prin(int a);
    void prin(Node& a);
public slots:
    void recev(QVector<QString> a);
    void recv(Node& aa);

public:
    void kk();
    void print();
private:
    Node a;
};

#endif // MYTESTA_H
