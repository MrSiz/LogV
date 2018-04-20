#include "datareader.h"

#include <QDebug>

DataReader::DataReader(QObject *parent) : QObject(parent)
{

}

LogHeaders DataReader::getFromConfig()
{

}

void DataReader::getData()
{
    qDebug() << "getData from the local text";
}
