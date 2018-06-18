#include "registerwindow.h"
#include "ui_registerwindow.h"
#include <QMessageBox>
RegisterWindow::RegisterWindow(Dao *arg, QWidget *parent) :
    dao(arg),
    QWidget(parent),
    ui(new Ui::RegisterWindow)
{
    ui->setupUi(this);
}

RegisterWindow::~RegisterWindow()
{
    delete ui;
}

void RegisterWindow::on_pushButton_pressed()
{
    if (dao->isExist(ui->uname->text())) {
        QMessageBox::about(this, tr("提示信息"), tr("用户已存在"));
    }else {
        bool flag =  dao->insertUser(ui->uname->text(), ui->pwd->text(),
                        ui->ip->text(), ui->suser->text(),
                        ui->spwd->text(), ui->path->text());
        if (flag) {
            QMessageBox::about(this, tr("提示信息"), tr("注册成功"));
            this->hide();
        }
        else {
            QMessageBox::about(this, tr("提示信息"), tr("注册失败"));

        }

    }
}
