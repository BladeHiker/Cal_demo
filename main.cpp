#include "cal.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Cal w;
    w.show();

    return a.exec();
}
