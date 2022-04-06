#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>
#include "entries.h"

namespace Ui {
class Signup;
}

class Signup : public QDialog
{
    Q_OBJECT

public:
    explicit Signup(QWidget *parent = nullptr);
    ~Signup();
public slots:
    void checkLineEdits();
private slots:
    void on_pushButton_next_clicked();

private:
    Ui::Signup *ui;
    Entries *entries;

};

#endif // SIGNUP_H
