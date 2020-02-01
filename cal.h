#ifndef CAL_H
#define CAL_H

#include <QWidget>
#include<QTextBrowser>
#include<QPushButton>
#include"info.h"
#include"help.h"
#include"exbase.h"
#include<exp.h>
namespace Ui {
class Cal;
}

class Cal : public QWidget
{
    Q_OBJECT

public:
    explicit Cal(QWidget *parent = nullptr);
    ~Cal();

private:
    Ui::Cal *ui;
    info *in;
    Help *helpwin;
    exbase *exbasewin;
    Exp *exp;
    QString *Log;
    QString placeholder;
};

#endif // CAL_H
