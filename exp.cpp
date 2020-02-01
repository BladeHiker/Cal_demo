#include "exp.h"
#include<string>
#include<cmath>
#include<QString>
#include<QVector>
#include<QStringList>
#include<QLocale>

Exp::Exp(QString str)
{
    exp(str);
}
bool Exp::ExpChk()
{
    const QVector<QChar> Qvec_char_chk_lst{'c','o','s','t','a','n','i','1','2','3','4','5','6','7','8','9','0','+','-','*','/','^','.','(',')',' ','p','e','l','n','q','r'};
    for(int i=0;i<Raw.size();++i)
    {
        bool fg_chk=false;
        for (auto &x:Qvec_char_chk_lst)
        {
            if(x==Raw.at(i))
            {
                fg_chk=true;
                break;
            }
        }
        if(!fg_chk)
            return false;
    }
    /*括号匹配*/
    int cnt=0;
    for (int i=0;i<Raw.size();++i)
    {
        if(Raw.at(i)=='(')
            ++cnt;
        else if(Raw.at(i)==')')
            --cnt;
    }
    if(cnt)
        return false;
    return true;
}
void Exp::ExpOpt()
{
    Exp_Opt="";
    for (int i=0;i<Raw.size();++i)
    {
        if(Raw.at(i)!=' ')
            Exp_Opt.append(Raw.at(i));
    }
}
QString Exp::toExpVal()
{
    if(!ExpChk())
        return "ERROR";
    if(Exp_Opt=="")
        return "0";
    return ExpBracketsCal(Exp_Opt);
}
QString Exp::ExpCal(QString exp)
{
    QStringList ExpPlusLst;
    QList<bool> ExpisPlusLst;
    QString exp_opt0;
    for(int i=0;i<exp.size();++i)
    {
        if(exp.at(i)=='-')
            exp_opt0.append("+-");
        else
            exp_opt0.append(exp.at(i));
    }
    ExpPlusLst=exp_opt0.split("+",QString::SkipEmptyParts);
    for(int i=0;i<ExpPlusLst.size();++i)
    {
        ExpisPlusLst.append(ExpPlusLst.at(i).at(0)!='-');
        if(ExpPlusLst.at(i).at(0)=='-')
            ExpPlusLst[i].remove(0,1);
    }


    QList<double> ExpPlusLstDouble;

    for(int x=0;x<ExpPlusLst.size();++x)
    {
        QString expt=ExpPlusLst[x];
        QStringList ExpMultLst;
        QList<bool> ExpisMultLst;
        QString exp_opt1;
        for(int i=0;i<expt.size();++i)
        {
            if(expt.at(i)=='/')
                exp_opt1.append("*/");
            else
                exp_opt1.append(expt.at(i));
        }
        ExpMultLst=exp_opt1.split("*",QString::KeepEmptyParts);
        for(int i=0;i<ExpMultLst.size();++i)
        {
            if(ExpMultLst[i]=="")
                return "ERROR";
            ExpisMultLst.append(ExpMultLst.at(i).at(0)!='/');
            if(ExpMultLst[i].at(0)=='/')
                ExpMultLst[i].remove(0,1);
        }

        for(int i=0;i<ExpMultLst.size();++i)
        {
            double tmps=1;
            QStringList ExpPowLst=ExpMultLst[i].split('^',QString::KeepEmptyParts);
            for(int i=ExpPowLst.size()-1;i>=0;--i)
            {
                if(ExpPowLst[i]=="")
                    return "ERROR";
                tmps=pow(ExpPowLst[i]=="p"?3.141592653589793:ExpPowLst[i]=="e"?2.718281828459:ExpPowLst[i].toDouble(),tmps);
            }
            ExpMultLst[i]=QString::number(tmps,'\0');
        }
        double tmpss=1;
        for(int i=0;i<ExpMultLst.size();++i)
        {
            if(ExpisMultLst[i])
                tmpss*=ExpMultLst[i]=="p"?3.141592653589793:ExpMultLst[i]=="e"?2.718281828459:ExpMultLst[i].toDouble();
            else
            {
                tmpss/=ExpMultLst[i]=="p"?3.141592653589793:ExpMultLst[i]=="e"?2.718281828459:ExpMultLst[i].toDouble();
            }
        }

        ExpPlusLstDouble.append(tmpss);
    }
    double S=0;
    for(int i=0;i<ExpPlusLstDouble.size();++i)
    {
        if(ExpisPlusLst[i])
            S+=ExpPlusLstDouble[i];
        else
        {
            S-=ExpPlusLstDouble[i];
        }
    }

    return QString::number(S,'\0');

}
QString Exp::ExpBracketsCal(QString exp)
{
    if(!exp.contains('(')&&!exp.contains(')'))
    {
        return ExpCal(exp);
    }
    QString Exp;
    QString Exp_t;
    int fg=0;
    enum fun{SIN,COS,TAN,LN,SQRT};
    int funcode=-1;
    for(int tt=0;tt<exp.size();++tt)
    {
        if(fg)
        {

            if(exp.at(tt)=='(')
            {
                fg++;
            }
            else if(exp.at(tt)==')')
            {
                fg--;
            }
            if(fg)
                Exp_t.append(exp.at(tt));
            else
            {
                if(funcode==-1)
                    Exp.append(ExpBracketsCal(Exp_t));
                else if(funcode==SIN)
                    Exp.append(QString::number(sin(ExpBracketsCal(Exp_t).toDouble()),'\0'));
                else if(funcode==COS)
                    Exp.append(QString::number(cos(ExpBracketsCal(Exp_t).toDouble()),'\0'));
                else if(funcode==TAN)
                    Exp.append(QString::number(tan(ExpBracketsCal(Exp_t).toDouble()),'\0'));
                else if(funcode==LN)
                    Exp.append(QString::number(log(ExpBracketsCal(Exp_t).toDouble()),'\0'));
                else if(funcode==SQRT)
                    Exp.append(QString::number(sqrt(ExpBracketsCal(Exp_t).toDouble()),'\0'));
                Exp_t="";
            }
        }
        else if(exp.at(tt)!='(')
        {
            Exp.append(exp.at(tt));
        }
        else if(exp.at(tt)=='(')
        {
            fg++;
            if(tt>2&&(exp.mid(tt-3,3))=="sin")
            {
                funcode=SIN;
                Exp.remove(Exp.size()-3,3);
            }
            else if(tt>2&&(exp.mid(tt-3,3))=="cos")
            {
                funcode=COS;
                Exp.remove(Exp.size()-3,3);
            }
            else if(tt>2&&(exp.mid(tt-3,3))=="tan")
            {
                funcode=TAN;
                Exp.remove(Exp.size()-3,3);
            }
            else if(tt>1&&(exp.mid(tt-2,2))=="ln")
            {
                funcode=LN;
                Exp.remove(Exp.size()-2,2);
            }
            else if(tt>3&&(exp.mid(tt-4,4))=="sqrt")
            {
                funcode=SQRT;
                Exp.remove(Exp.size()-4,4);
            }
            else
            {
                funcode=-1;
            }
        }

    }
    return ExpBracketsCal(Exp);
}
void Exp::exp(QString str)
{
    Raw=str;
    Exp_Opt="";
    ExpOpt();
}
