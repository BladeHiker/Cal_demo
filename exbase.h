#ifndef EXBASE_H
#define EXBASE_H

#include <QDialog>

namespace Ui {
class exbase;
}

class exbase : public QDialog
{
    Q_OBJECT

public:
    explicit exbase(QWidget *parent = nullptr);
    ~exbase();

private:
    Ui::exbase *ui;
};

#endif // EXBASE_H
