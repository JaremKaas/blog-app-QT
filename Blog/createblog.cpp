#include "createblog.h"
#include "ui_createblog.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonParseError>

#include <QFile>
#include <QTextStream>
#include <QMessageBox>

CreateBlog::CreateBlog(QWidget *parent,int new_authorID,QString new_authorEmail) :
    QDialog(parent),
    ui(new Ui::CreateBlog)
{
    ui->setupUi(this);
    authorID=new_authorID;
    authorEmail=new_authorEmail;
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

    QFile fileBlog("blog"+QString::number(authorID)+".json");
    if (!fileBlog.open(QFile::WriteOnly | QFile::Truncate))
        QMessageBox::warning(this,"File error","Json file cannot be opened");

    QJsonObject rootObj;
    QJsonArray entArr;
    rootObj.insert("title",blogTitle);
    rootObj["entries"]=entArr;
    QJsonDocument doc;
    doc.setObject(rootObj);

    // Write the content to the file
    QTextStream wirteStream(&fileBlog);
    wirteStream <<doc.toJson(); 		// write file
    fileBlog.close();
}

