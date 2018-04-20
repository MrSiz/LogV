#include "downloader.h"
#include <QTimer>
#include <QProcess>
#include <Python.h>
#include <QDebug>

Downloader::Downloader(QObject *parent) :
    QObject(parent),
    timer(new QTimer())
{
    connect(timer, SIGNAL(timeout()), this, SLOT(download()));
}

void Downloader::work()
{
    const int msec = 5e3;
    timer->start(msec);
}

void Downloader::download() const
{
//    QProcess::execute("python /home/mrsiz/downloader.py");
    Py_Initialize();
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('./../LogV/')");
    PyObject* pModule = PyImport_Import(PyString_FromString("down"));
    if (!pModule) {
        qDebug() << "i can not open the file";
        return ;
    }
    PyObject* pFunhello= PyObject_GetAttrString(pModule,"A");
    if (!pFunhello) {
        qDebug() << "load the function fail";
        return ;
    }
    PyObject* value = PyObject_CallFunction(pFunhello,NULL);
    int res = PyInt_AsLong(value);
    qDebug() << "res is " << res;
    Py_Finalize();

    emit update();
}
