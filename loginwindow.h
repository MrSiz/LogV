#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include "dao.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(Dao *arg, QWidget *parent = 0);
    ~LoginWindow();
signals:
    void enterMainWindow();
    void enterRegisterWindow();
private slots:
    void on_loginButton_pressed();

    void on_registerButton_pressed();

private:
    bool checkUser() const;

private:
    Ui::LoginWindow *ui;

    Dao *dao;

};

#endif // LOGINWINDOW_H
