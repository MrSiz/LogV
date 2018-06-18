#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>

class QTimer;

class Downloader : public QObject
{
    Q_OBJECT
public:
    explicit Downloader(QObject *parent = nullptr);

    ~Downloader();
signals:
    void update() const;
public slots:
    void download() const;
    void work();
private:
    QTimer *timer;
    QThread *downThread;
};

#endif // DOWNLOADER_H
