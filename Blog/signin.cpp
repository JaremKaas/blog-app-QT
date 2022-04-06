#include "signin.h"
#include "ui_signin.h"
#include <QMessageBox>

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonParseError>

#include <QDebug>
#include <QFile>
#include <QTextStream>

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


void SignIn::on_pushButton_signin_clicked()
{
    QString user_email = ui->lineEdit_email->text();           //write content from edit lines
    QString user_password = ui->lineEdit_password->text();     //write content from edit lines

    QFile fileUsers("users.json");                             // Open file
    if (!fileUsers.open(QFile::ReadOnly | QFile::Text))
        QMessageBox::warning(this,"File error","Json file cannot be opened");

    QTextStream stream(&fileUsers); // Read the entire contents of the file
    QString str = stream.readAll(); // Read the entire contents of the file
    fileUsers.close();

    QJsonParseError jsonParseError;
    QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8(), &jsonParseError);
    if (jsonParseError.error != QJsonParseError::NoError && !doc.isNull())
        QMessageBox::warning(this,"Json Format error!","Json Format error!");

    QJsonObject rootObj = doc.object();

    // find registrated user with entered email and password
    QJsonValue usersValue = rootObj.value("users");
    if (usersValue.type() == QJsonValue::Array) {
        QJsonArray usersArr = usersValue.toArray();

        for(int i=0; usersArr.size()>i;i++)
        {
            QJsonValue userValue = usersArr.at(i);
            if (userValue.type() == QJsonValue::Object) {
                QJsonObject userObj = userValue.toObject();

                QString emailValue = userObj.value("email").toString();
                QString passwordValue = userObj.value("password").toString();

                if(user_email == emailValue && user_password==passwordValue)
                {
                    int authorIDValue=userObj.value("id").toInt();
                    entries= new Entries(this,authorIDValue,emailValue);
                    entries->show();
                    hide();
                }
            }
        }
        // there where no user in the .json file that has given email and password
        ui->label_wrongdata->setText("Wrong email or password");
        ui->lineEdit_email->clear();
        ui->lineEdit_password->clear();
    }
}

void SignIn::on_pushButton_signup_clicked()
{
    hide();
    signup =new Signup(this);
    signup->show();
}

