#include "addentry.h"
#include "ui_addentry.h"
#include <QTime>
#include <QDate>

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonParseError>

#include <QFile>
#include <QTextStream>
#include <QMessageBox>
AddEntry::AddEntry(QWidget *parent,int new_authorID,QString new_authorEmail) :
    QDialog(parent),
    ui(new Ui::AddEntry)
{
    ui->setupUi(this);
    authorID=new_authorID;
   authorEmail=new_authorEmail;
}

AddEntry::~AddEntry()
{
    delete ui;
}

void AddEntry::on_pushButton_add_clicked()
{
    QString content = ui->plainTextEdit_content->toPlainText();
    QString creationTime = QTime::currentTime().toString();
    QString creationDate = QDate::currentDate().toString();

    QString fileName="blog"+QString::number(authorID)+".json";
    QFile fileBlog(fileName);
    if (!fileBlog.open(QFile::ReadOnly | QFile::Text))
        QMessageBox::warning(this,"File error","Json file cannot be opened");

    QTextStream stream(&fileBlog); // Read the entire contents of the file
    QString str = stream.readAll();
    fileBlog.close();

    QJsonParseError jsonParseError;
    QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8(), &jsonParseError);
    if (jsonParseError.error != QJsonParseError::NoError && !doc.isNull())
        QMessageBox::warning(this,"Json Format error!","Json Format error!");

     QJsonObject rootObj = doc.object();
     QJsonValue entriesValue = rootObj.value("entries");
     if (entriesValue.type() == QJsonValue::Array) {
         QJsonArray entriesArr = entriesValue.toArray();
         QJsonObject newEntry;                   // create an object for new user
         newEntry.insert("creationTime", creationTime);
         newEntry.insert("creationDate", creationDate);
         newEntry.insert("content",content);

         entriesArr.append(newEntry);  // add new user to the array
         rootObj["entries"] = entriesArr; // and root object
         doc.setObject(rootObj);

         // Rewrite the file
         QFile fileWrite(fileName);
         if (!fileWrite.open(QFile::WriteOnly | QFile::Truncate))
            QMessageBox::warning(this,"File error","Json file cannot be opened2");

         // Write the modified content to the file
         QTextStream wirteStream(&fileWrite);
         wirteStream << doc.toJson();		// write file
         fileWrite.close();
     }
}
