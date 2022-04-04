#ifndef CREATEBLOG_H
#define CREATEBLOG_H

#include <QDialog>

namespace Ui {
class CreateBlog;
}

class CreateBlog : public QDialog
{
    Q_OBJECT
    QString authorID;

public:
    explicit CreateBlog(QWidget *parent = nullptr,QString new_authorID="");
    ~CreateBlog();
public slots:
    void checkLineEdits();

private slots:
    void on_pushButton_ok_clicked();

private:
    Ui::CreateBlog *ui;
};

#endif // CREATEBLOG_H
