#ifndef SIGNIN_H
#define SIGNIN_H

#include <QMainWindow>
#include "entries.h"

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
private:
    Ui::SignIn *ui;
    Entries *entries;
};
#endif // SIGNIN_H
