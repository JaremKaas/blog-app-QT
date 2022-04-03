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

    if(rootObj.empty())
    {
        ui->groupBox_1->setVisible(false);
        ui->label_title->clear();
        ui->label_id->clear();
        ui->label_author->clear();
        ui->label_content->clear();
        ui->pushButton_create->setEnabled(true);
        ui->pushButton_delete->setEnabled(false);
    }
    else
    {
        QString authorValue = rootObj.value("author").toString();
        ui->label_id->setText("ID: "+authorID);
        ui->label_author->setText("Author: "+authorValue);
        QString titleValue = rootObj.value("title").toString();
        ui->label_title->setText(titleValue);

        QJsonValue entriesValue = rootObj.value("entries");
        if (entriesValue.type() == QJsonValue::Array) {
            QJsonArray entriesArr = entriesValue.toArray();
            QJsonValue entriesValue = entriesArr.at(0);
                if (entriesValue.type() == QJsonValue::Object) {
                    QJsonObject entriesObj = entriesValue.toObject();
                    QString timeValue = entriesObj.value("creationTime").toString();
                    QString dateValue = entriesObj.value("date").toString();
                    QString contentValue = entriesObj.value("content").toString();
                    if(!timeValue.isEmpty() && !dateValue.isEmpty() && !contentValue.isEmpty()) //if entry exists
                    {
                        ui->label_content->setText(contentValue);
                        ui->groupBox_1->setTitle(dateValue+" "+timeValue);
                    }
                    else
                        ui->groupBox_1->setVisible(false);
                }
            }
    }

}

Entries::~Entries()
{
    delete ui;
}

void Entries::on_pushButton_delete_clicked()
{
    QMessageBox::StandardButton confirm;
      confirm = QMessageBox::question(this, "Delete blog", "Do you want to delete this blog?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (confirm == QMessageBox::Yes) {
        qDebug() << "Yes was clicked";
        ui->label_title->setText("deleted");
      } else {
        qDebug() << "Yes was *not* clicked";
      }
}

