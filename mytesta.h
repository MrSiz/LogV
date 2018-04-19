#ifndef MYTESTA_H
#define MYTESTA_H

#include <QObject>
#include <QVector>
class MyTestA : public QObject
{
    Q_OBJECT
public:
    explicit MyTestA(QObject *parent = nullptr);

signals:
    void prin(int a);
public slots:
    void recev(QVector<QString> a);

public:
    void kk();
};

#endif // MYTESTA_H
