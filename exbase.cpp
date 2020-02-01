#include "exbase.h"
#include "ui_exbase.h"
#include<QString>
#include<QDebug>
exbase::exbase(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::exbase)
{
    ui->setupUi(this);
    connect(ui->lineEdit,&QLineEdit::textChanged,[&](){
        bool ok;
        QString str;
        ui->lineEdit->setText(ui->lineEdit->text().toUpper());
        str.setNum(ui->lineEdit->text().toLongLong(&ok,16),10);
        ui->lineEdit_2->setText(str);
        str.setNum(ui->lineEdit->text().toLongLong(&ok,16),8);
        ui->lineEdit_3->setText(str);
        str.setNum(ui->lineEdit->text().toLongLong(&ok,16),2);
        ui->lineEdit_4->setText(str);
    });
    connect(ui->lineEdit_2,&QLineEdit::textChanged,[&](){
        bool ok;
        QString str;
        str.setNum(ui->lineEdit_2->text().toLongLong(&ok,10),16).toUpper();
        ui->lineEdit->setText(str);
        str.setNum(ui->lineEdit_2->text().toLongLong(&ok,10),8);
        ui->lineEdit_3->setText(str);
        str.setNum(ui->lineEdit_2->text().toLongLong(&ok,10),2);
        ui->lineEdit_4->setText(str);
    });
    connect(ui->lineEdit_3,&QLineEdit::textChanged,[&](){
        bool ok;
        QString str;
        str.setNum(ui->lineEdit_3->text().toLongLong(&ok,8),16).toUpper();
        ui->lineEdit->setText(str);
        str.setNum(ui->lineEdit_3->text().toLongLong(&ok,8),10);
        ui->lineEdit_2->setText(str);
        str.setNum(ui->lineEdit_3->text().toLongLong(&ok,8),2);
        ui->lineEdit_4->setText(str);
    });
    connect(ui->lineEdit_4,&QLineEdit::textChanged,[&](){
        bool ok;
        QString str;
        str.setNum(ui->lineEdit_4->text().toLongLong(&ok,2),10);
        ui->lineEdit_2->setText(str);
        str.setNum(ui->lineEdit_4->text().toLongLong(&ok,2),8);
        ui->lineEdit_3->setText(str);
        str.setNum(ui->lineEdit_4->text().toLongLong(&ok,2),16).toUpper();
        ui->lineEdit->setText(str);
    });

}

exbase::~exbase()
{
    delete ui;
}
