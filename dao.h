#ifndef DAO_H
#define DAO_H

#include <QObject>
#include <QSqlDatabase>

class Dao : public QObject
{
    Q_OBJECT
public:
    explicit Dao(QObject *parent = nullptr);

signals:

public slots:

public:
    bool isExist(const QString &usr, const QString &pwd) const;
    bool isExist(const QString &id) const;
    bool insertUser(const QString &user,
                    const QString &pwd,
                    const QString &srvIp,
                    const QString &srvUsr,
                    const QString &srvPwd,
                    const QString &path) const;
private:
    QSqlDatabase db;
};

#endif // DAO_H
