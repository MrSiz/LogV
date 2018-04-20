#include "mytesta.h"
#include <QDebug>

MyTestA::MyTestA(QObject *parent) : QObject(parent)
{

}

void MyTestA::recev(QVector<QString> a)
{
    qDebug() << "receive";
    qDebug() << a << endl;

}

void MyTestA::recv(Node &aa)
{
    qDebug() << "recevie NOde a";
    aa.a = 2;
}

void MyTestA::kk()
{
    emit prin(this->a);
}

void MyTestA::print()
{
    qDebug() << this->a.a;
}


