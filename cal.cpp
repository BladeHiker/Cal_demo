#include "cal.h"
#include "ui_cal.h"
#include"info.h"
#include"ui_info.h"
#include<exp.h>
Cal::Cal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Cal)
{
    ui->setupUi(this);
    in=new info;
    helpwin=new Help;
    exbasewin=new exbase;
    exp=new Exp("0");
    Log=new QString;

    ui->lineEdit->setFocus();
    placeholder="Enter Math Expression Here";
    ui->dial->setRange(30,100);
    connect(ui->dial,&QDial::valueChanged,this,[&](){this->setWindowOpacity(ui->dial->value()/100.0);});


    //PushButton
    ui->lineEdit->setPlaceholderText(placeholder);
    connect(ui->pushButton_7,&QPushButton::clicked,ui->lineEdit,&QLineEdit::clear);
    connect(ui->pushButton_7,&QPushButton::clicked,ui->lcdNumber,[this](){ui->lcdNumber->display("0");});   
    connect(ui->pushButton_15,&QPushButton::clicked,ui->lineEdit,[this](){ui->lineEdit->insert("1");});
    connect(ui->pushButton_18,&QPushButton::clicked,ui->lineEdit,[this](){ui->lineEdit->insert("2");});
    connect(ui->pushButton_21,&QPushButton::clicked,ui->lineEdit,[this](){ui->lineEdit->insert("3");});
    connect(ui->pushButton_14,&QPushButton::clicked,ui->lineEdit,[this](){ui->lineEdit->insert("4");});
    connect(ui->pushButton_17,&QPushButton::clicked,ui->lineEdit,[this](){ui->lineEdit->insert("5");});
    connect(ui->pushButton_20,&QPushButton::clicked,ui->lineEdit,[this](){ui->lineEdit->insert("6");});
    connect(ui->pushButton_13,&QPushButton::clicked,ui->lineEdit,[this](){ui->lineEdit->insert("7");});
    connect(ui->pushButton_16,&QPushButton::clicked,ui->lineEdit,[this](){ui->lineEdit->insert("8");});
    connect(ui->pushButton_19,&QPushButton::clicked,ui->lineEdit,[this](){ui->lineEdit->insert("9");});
    connect(ui->pushButton_22,&QPushButton::clicked,ui->lineEdit,[this](){ui->lineEdit->insert("0");});
    connect(ui->pushButton_24,&QPushButton::clicked,ui->lineEdit,[this](){ui->lineEdit->insert("(");});
    connect(ui->pushButton_25,&QPushButton::clicked,ui->lineEdit,[this](){ui->lineEdit->insert(")");});
    connect(ui->pushButton_23,&QPushButton::clicked,ui->lineEdit,[this](){ui->lineEdit->insert(".");});
    connect(ui->pushButton_8,&QPushButton::clicked,ui->lineEdit,[this](){ui->lineEdit->insert("+");});
    connect(ui->pushButton_9,&QPushButton::clicked,ui->lineEdit,[this](){ui->lineEdit->insert("-");});
    connect(ui->pushButton_10,&QPushButton::clicked,ui->lineEdit,[this](){ui->lineEdit->insert("*");});
    connect(ui->pushButton_11,&QPushButton::clicked,ui->lineEdit,[this](){ui->lineEdit->insert("/");});
    connect(ui->pushButton_6,&QPushButton::clicked,ui->lineEdit,[this](){ui->lineEdit->insert("^");});
    connect(ui->pushButton_2,&QPushButton::clicked,ui->lineEdit,[this](){ui->lineEdit->insert("sin(");});
    connect(ui->pushButton_3,&QPushButton::clicked,ui->lineEdit,[this](){ui->lineEdit->insert("cos(");});
    connect(ui->pushButton_4,&QPushButton::clicked,ui->lineEdit,[this](){ui->lineEdit->insert("tan(");});
    connect(ui->pushButton_5,&QPushButton::clicked,ui->lineEdit,[this](){ui->lineEdit->insert("sqrt(");});
    connect(ui->pushButton_26,&QPushButton::clicked,ui->lineEdit,[this](){ui->lineEdit->insert("^2");});
    connect(ui->pushButton_27,&QPushButton::clicked,ui->lineEdit,[this](){ui->lineEdit->insert("p");});
    connect(ui->pushButton_37,&QPushButton::clicked,ui->lineEdit,[this](){ui->lineEdit->insert("e");});
    connect(ui->pushButton_38,&QPushButton::clicked,ui->lineEdit,[this](){ui->lineEdit->insert("ln(");});
    connect(ui->pushButton_29,&QPushButton::clicked,ui->lineEdit,[this](){ui->lineEdit->backspace();});
    connect(ui->pushButton_39,&QPushButton::clicked,[&](){in->show();});
    connect(ui->pushButton_12,&QPushButton::clicked,[&](){helpwin->show();});
    connect(ui->pushButton_28,&QPushButton::clicked,[&](){exbasewin->show();});
    connect(ui->lineEdit,&QLineEdit::textEdited,[&](){
        ui->textBrowser->setText(ui->lineEdit->text()+"\n"+Log);
       // ui->textBrowser->forward();
    });
    connect(ui->pushButton,&QPushButton::clicked,[&](){
        this->exp->exp(ui->lineEdit->text());
        ui->lcdNumber->display(this->exp->toExpVal());
        Log->insert(0,ui->lineEdit->text()+"  =  "+this->exp->toExpVal()+"\n");
        ui->textBrowser->setText(*Log);
        //ui->textBrowser->forward();
         });



    ui->textBrowser->setStyleSheet("background-color:transparent;");
    /*ui->pushButton->setShortcut(Qt::Key_Enter);
    connect(ui->lineEdit,&QLineEdit::returnPressed,[&](){
        this->exp->exp(ui->lineEdit->text());
        ui->lcdNumber->display(this->exp->toExpVal());
        Log->push_front(ui->lineEdit->text()+"  =  "+this->exp->toExpVal()+"\n");
        ui->textBrowser->append(*this->Log);
        ui->textBrowser->forward();
         });*/

}

Cal::~Cal()
{
    delete ui;
    delete in;
    delete helpwin;
    delete exbasewin;
    delete exp;
    delete Log;
}
