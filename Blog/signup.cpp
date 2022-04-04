#include "signup.h"
#include "ui_signup.h"

Signup::Signup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Signup)
{
    ui->setupUi(this);
    connect(ui->lineEdit_email,&QLineEdit::textChanged,this,&Signup::checkLineEdits);
    connect(ui->lineEdit_id,&QLineEdit::textChanged,this,&Signup::checkLineEdits);
    connect(ui->lineEdit_password_1,&QLineEdit::textChanged,this,&Signup::checkLineEdits);
    connect(ui->lineEdit_password_2,&QLineEdit::textChanged,this,&Signup::checkLineEdits);
}

void Signup::checkLineEdits()
{
    bool filled= !ui->lineEdit_email->text().isEmpty()&& !ui->lineEdit_id->text().isEmpty() &&
            !ui->lineEdit_password_1->text().isEmpty() && !ui->lineEdit_password_2->text().isEmpty();
    bool password_match= ui->lineEdit_password_1->text() == ui->lineEdit_password_2->text();
    ui->pushButton_next->setEnabled(filled&&password_match);
    ui->pushButton_createblog->setEnabled(filled&&password_match);
    if(!password_match)
        ui->label_wrongpassword->setText("Passwords are not identical");
    else
        ui->label_wrongpassword->clear();
}


Signup::~Signup()
{
    delete ui;
}
