#ifndef ADD_H
#define ADD_H

#include <QDialog>

namespace Ui {
class Add;
}

class Add : public QDialog
{
    Q_OBJECT
    int authorID;

public:
    explicit Add(QWidget *parent = nullptr,int authorID=0);
    ~Add();

private slots:
    void on_pushButton_add_clicked();

private:
    Ui::Add *ui;
};

#endif // ADD_H
