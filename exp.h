#ifndef EXP_H
#define EXP_H
#include<bits/stdc++.h>
#include<QString>
#include<QVector>
#include<QStringList>
class Exp
{
private:
    QString Raw;
    QString Exp_Opt;
public:
    Exp(QString str);
    void exp(QString str);
    bool ExpChk();//表达式合法性检查
    void ExpOpt();//表达式优化
    QString ExpCal(QString exp);//无括号表达式计算
    QString ExpBracketsCal(QString exp);//括号展开计算
    QString toExpVal();
};

#endif // EXP_H
