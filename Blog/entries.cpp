#include "entries.h"
#include "ui_entries.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonParseError>

#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

Entries::Entries(QWidget *parent,QString authorID) :
    QDialog(parent),
    ui(new Ui::Entries)
{
    ui->setupUi(this);

    // read blog entries from file blog+authorID
    QString fileName="blog"+authorID+".json";
    QFile file(fileName);
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
    QJsonValue entriesValue = rootObj.value("entries");
    if (entriesValue.type() == QJsonValue::Array) {
        QJsonArray entriesArr = entriesValue.toArray();
        QJsonValue entriesValue = entriesArr.at(0);
            if (entriesValue.type() == QJsonValue::Object) {
                QJsonObject userObj = entriesValue.toObject();
                QString timeValue = userObj.value("creationTime").toString();
                QString dateValue = userObj.value("date").toString();
                QString authorValue = userObj.value("author").toString();
                QString titleValue = userObj.value("title").toString();
                QString contentValue = userObj.value("content").toString();

                ui->label_title->setText(titleValue);
                ui->label_id->setText("ID: "+authorID);
                ui->label_author->setText("Author: "+authorValue);
                ui->label_content->setText(contentValue);

                ui->groupBox_1->setTitle(dateValue+" "+timeValue);
            }
            else
            {
                ui->groupBox_1->setVisible(false);
                ui->label_title->clear();
                ui->label_id->clear();
                ui->label_author->clear();
                ui->label_content->clear();
            }
        }
}

Entries::~Entries()
{
    delete ui;
}
