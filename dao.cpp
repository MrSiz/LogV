#include "dao.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
Dao::Dao(QObject *parent) : QObject(parent)
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("118.89.243.43");
    db.setDatabaseName("logV");
    qDebug() << "try connecting";
    db.setPort(3306);
    db.setUserName("root");
    db.setPassword("zhaohuan");
    qDebug() << "werwer";
    if (db.open()) {
        qDebug() << "connect successfully";
    }else {
        qDebug() << db.lastError();
        qDebug() << "errror for db";
    }
}

bool Dao::isExist(const QString &id) const
{
    QString sql = "select * from user_tbl where username = '" + id + "'";

    QSqlQuery query;
    query.exec(sql);
    if (query.size() == 0) return false;
    return true;
}

bool Dao::insertUser(const QString &user, const QString &pwd, const QString &srvIp, const QString &srvUsr, const QString &srvPwd, const QString &path) const
{
    QString sql = "INSERT INTO `user_tbl`(`username`, `passwd`, `servip`, `servuser`, `servpwd`, "
                   "`servpath`) VALUES ('" + user +"','"
             + pwd + "','" + srvIp + "','" + srvUsr + "','" + srvPwd + "','" + path + "')";

    QSqlQuery query;
    if (query.exec(sql)) return true;
    qDebug() << "insert dataTable Error";
    qDebug() << query.lastError();
    return false;

}

bool Dao::isExist(const QString &usr, const QString &pwd) const
{
    QString sql = "select * from user_tbl where username = '" + usr + "' and passwd = '"
            + pwd + "'";

    QSqlQuery query;
    query.exec(sql);
    if (query.size() == 1) return true;
    return false;

}
