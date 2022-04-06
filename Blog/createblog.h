#ifndef CREATEBLOG_H
#define CREATEBLOG_H

#include <QDialog>
#include "addentry.h"

namespace Ui {
class CreateBlog;
}

class CreateBlog : public QDialog
{
    Q_OBJECT
    int authorID;
    QString authorEmail;

public:
    explicit CreateBlog(QWidget *parent = nullptr,int new_authorID=0,QString authorEmail="");
    ~CreateBlog();
public slots:
    void checkLineEdits();

private slots:
    void on_pushButton_ok_clicked();

private:
    Ui::CreateBlog *ui;
    AddEntry *addEn;

};

#endif // CREATEBLOG_H
