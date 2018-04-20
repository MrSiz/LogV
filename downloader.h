#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>

class QTimer;

class Downloader : public QObject
{
    Q_OBJECT
public:
    explicit Downloader(QObject *parent = nullptr);
    void work();
signals:
    void update() const;
public slots:
    void download() const;
private:
    QTimer *timer;
};

#endif // DOWNLOADER_H
