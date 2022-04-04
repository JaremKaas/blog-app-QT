#include "createblog.h"
#include "ui_createblog.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonParseError>

#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

CreateBlog::CreateBlog(QWidget *parent,QString new_authorID) :
    QDialog(parent),
    ui(new Ui::CreateBlog)
{
    ui->setupUi(this);
    authorID=new_authorID;
    connect(ui->lineEdit_title,&QLineEdit::textChanged,this,&CreateBlog::checkLineEdits);
}

void CreateBlog::checkLineEdits()
{
    ui->pushButton_ok->setEnabled(!ui->lineEdit_title->text().isEmpty());
}

CreateBlog::~CreateBlog()
{
    delete ui;
}

void CreateBlog::on_pushButton_ok_clicked()
{
    QString blogTitle=ui->lineEdit_title->text();

    QFile file="blog"+authorID+".json";
    if (!file.open(QFile::WriteOnly | QFile::Truncate))
        QMessageBox::warning(this,"File error","Json file cannot be opened");

    QJsonObject rootObj;
    QJsonArray entries;
    QJsonObject entry_1;
    entries.append(entry_1);
    rootObj["entries"]=entries;
    rootObj.insert("title",blogTitle);
    QJsonDocument doc;
    doc.setObject(rootObj);
    // Write the modified content to the file
    QTextStream wirteStream(&file);
    wirteStream <<doc.toJson(); 		// write file
    file.close();
    hide();

}

