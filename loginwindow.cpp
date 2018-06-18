#include "loginwindow.h"
#include "ui_loginwindow.h"

#include <QMessageBox>
#include <QDebug>

LoginWindow::LoginWindow(Dao *arg, QWidget *parent) :
    dao(arg),
    QWidget(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

bool LoginWindow::checkUser() const
{
        qDebug() << ui->userName->text();
    qDebug() << ui->passwd->text();

    return true;
}

void LoginWindow::on_loginButton_pressed()
{
//dao->isExist(ui->userName->text(), ui->passwd->text())
    if (dao->isExist(ui->userName->text(), ui->passwd->text())){
       emit enterMainWindow();
       this->hide();
    }
    else
        QMessageBox::about(this, tr("提示信息"), tr("账号或密码错误"));

}

void LoginWindow::on_registerButton_pressed()
{
    emit enterRegisterWindow();
}
