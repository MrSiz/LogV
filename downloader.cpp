#include "downloader.h"
#include <QTimer>
#include <QProcess>
#include <Python.h>
#include <QDebug>
#include <time.h>
#include <stdlib.h>
#include <QThread>
Downloader::Downloader(QObject *parent) :
    QObject(parent),
    timer(new QTimer())
{

    const int msec = 5e3;
    QThread *downThread= new QThread;
    timer->moveToThread(downThread);
    timer->setInterval(msec);
    connect(downThread, SIGNAL(started()), timer, SLOT(start()));
    connect(timer, SIGNAL(timeout()), this, SLOT(download()), Qt::DirectConnection);
    downThread->start();


}

void Downloader::work()
{
    const int msec = 5e3;
    timer->start(msec);
    qDebug() << "work in " << QThread::currentThreadId();
}

Downloader::~Downloader()
{
    qDebug() << "downloader destructor " << QThread::currentThreadId();
}

void Downloader::download() const
{
//    QProcess::execute("python /home/mrsiz/downloader.py");
    clock_t start, end;
    start = clock();
    qDebug() << "download in thread " << QThread::currentThreadId();
    Py_Initialize();
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('./../LogV/')");
    PyObject* pModule = PyImport_Import(PyString_FromString("down"));
    if (!pModule) {
        qDebug() << "i can not open the file";
        return ;
    }
    PyObject* pFunhello= PyObject_GetAttrString(pModule,"work");
    if (!pFunhello) {
        qDebug() << "load the function fail";
        return ;
    }
    PyObject* value = PyObject_CallFunction(pFunhello,NULL);
    if (!value) {
        qDebug() << "call function fail";
    }
    int res = PyInt_AsLong(value);
    qDebug() << "res is " << res;
    Py_Finalize();

    emit update();
    end = clock();
    qDebug() << (double)(end - start) / CLOCKS_PER_SEC;// << endl;
}
