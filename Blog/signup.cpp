#include "signup.h"
#include "ui_signup.h"

#include <QMessageBox>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonParseError>

#include <QFile>
#include <QTextStream>
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

    ui->pushButton_next->setEnabled(filled&&password_match);     //registration possible only if all required data are provided and...
    if(!password_match)                                          //passwords are identical
        ui->label_wrongpassword->setText("Passwords are not identical");
    else
        ui->label_wrongpassword->clear();
}


Signup::~Signup()
{
    delete ui;
}

void Signup::on_pushButton_next_clicked()
{
    QString user_email = ui->lineEdit_email->text();
    QString user_password_1 = ui->lineEdit_password_1->text();
    int user_id = ui->lineEdit_id->text().toInt();


    QFile fileUsers("users.json");
    if (!fileUsers.open(QFile::ReadOnly | QFile::Text))
        QMessageBox::warning(this,"File error","Json file cannot be opened1");

    QTextStream stream(&fileUsers); // Read the entire contents of the file
    QString str = stream.readAll();

    QJsonParseError jsonParseError; // Check json format errors
    QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8(), &jsonParseError);
    if (jsonParseError.error != QJsonParseError::NoError && !doc.isNull())
        QMessageBox::warning(this,"Json Format error!","Json Format error!");

    QJsonObject rootObj = doc.object(); // root object
    QJsonValue usersValue = rootObj.value("users"); // looking for an array
    if (usersValue.type() == QJsonValue::Array)
    {
        QJsonArray usersArr = usersValue.toArray(); // array is found
        bool ID_unique=true;        // both id and email has to be unique
        bool email_unique=true;     //
        for(int i=0; usersArr.size()>i;i++)
        {
            QJsonValue userValue = usersArr.at(i);
            if (userValue.type() == QJsonValue::Object)
            {
                QJsonObject userObj = userValue.toObject();
                int idValue = userObj.value("id").toInt();
                QString emailValue = userObj.value("email").toString();
                if(idValue==user_id)
                {
                    QMessageBox::about(this,"Wrong ID","User with this ID number already exists. Use different ID.");
                    ID_unique=false;
                    ui->lineEdit_id->clear();
                }
                if(emailValue==user_email)
                {
                    QMessageBox::about(this,"Wrong email","User with this E-mail address already exists.");
                    email_unique=false;
                    ui->lineEdit_email->clear();
                }

            }
        }
        if(ID_unique && email_unique)
        {
            QJsonObject newUser;                   // create an object for new user
            newUser.insert("email", user_email);
            newUser.insert("password", user_password_1);
            newUser.insert("id",user_id);

            usersArr.append(newUser);  // add new user to the array
            rootObj["users"] = usersArr; // and root object
            doc.setObject(rootObj);
            // Rewrite the file
            QFile writeFile("users.json");
            if (!writeFile.open(QFile::WriteOnly | QFile::Truncate))
               QMessageBox::warning(this,"File error","Json file cannot be opened2");

            // Write the modified content to the file
            QTextStream wirteStream(&writeFile);
            wirteStream << doc.toJson();		// write file
            writeFile.close();

            hide();
            entries = new Entries(this,user_id,user_email);
            entries->show();
        }
    }
}


