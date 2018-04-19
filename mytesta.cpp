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

//void MyTestA::prin(int a) {
//    a = 1;
//}
