#include "signin.h"
#include "ui_signin.h"

SignIn::SignIn(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SignIn)
{
    ui->setupUi(this);
    connect(ui->lineEdit_email,&QLineEdit::textChanged,this,&SignIn::checkLineEdits);
    connect(ui->lineEdit_password,&QLineEdit::textChanged,this,&SignIn::checkLineEdits);
}

void SignIn::checkLineEdits()
{
    bool filled= !ui->lineEdit_email->text().isEmpty()&& !ui->lineEdit_password->text().isEmpty();
    ui->pushButton_signin->setEnabled(filled);
}

SignIn::~SignIn()
{
    delete ui;
}

