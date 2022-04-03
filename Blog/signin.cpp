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
    QString user_email = ui->lineEdit_email->text();
    QString user_password = ui->lineEdit_password->text();

    QFile file("users.json");
    if (!file.open(QFile::ReadOnly | QFile::Text))
        QMessageBox::warning(this,"File error","Json file cannot be opened");

    QTextStream stream(&file); // Read the entire contents of the file
    QString str = stream.readAll();
    file.close();

    QJsonParseError jsonParseError;
    QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8(), &jsonParseError);
    if (jsonParseError.error != QJsonParseError::NoError && !doc.isNull())
        QMessageBox::warning(this,"Json Format error!","Json Format error!");

    QJsonObject rootObj = doc.object();

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
                QString authorIDValue=userObj.value("id").toString();
                if(user_email == emailValue && user_password==passwordValue)
                {
                    ui->label_wrongdata->setText("succes");
                }
            }
        }
        ui->label_wrongdata->setText("Wrong email or password");
        ui->lineEdit_email->clear();
        ui->lineEdit_password->clear();
    }
}

