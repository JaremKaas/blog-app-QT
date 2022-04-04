#ifndef SIGNIN_H
#define SIGNIN_H

#include <QMainWindow>
#include "entries.h"
#include "signup.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SignIn; }
QT_END_NAMESPACE

class SignIn : public QMainWindow
{
    Q_OBJECT

public:
    SignIn(QWidget *parent = nullptr);
    ~SignIn();

private slots:
    void on_pushButton_signin_clicked();
    void checkLineEdits();
    void on_pushButton_signup_clicked();

private:
    Ui::SignIn *ui;
    Entries *entries;
    Signup *signup;
};
#endif // SIGNIN_H
