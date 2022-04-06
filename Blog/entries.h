#ifndef ENTRIES_H
#define ENTRIES_H

#include <QDialog>
#include "createblog.h"


namespace Ui {
class Entries;
}

class Entries : public QDialog
{
    Q_OBJECT
    QString authorEmail; //email
    int authorID;

public:
    explicit Entries(QWidget *parent = nullptr, int new_authorID=0,QString new_authorEmail="");
    ~Entries();
    void refresh();

private slots:
    void on_pushButton_delete_clicked();

    void on_pushButton_create_clicked();

    void ifBlogExists(bool blogExists);

    void on_pushButton_add_clicked();

private:
    Ui::Entries *ui;
    CreateBlog *createBlog;
};

#endif // ENTRIES_H
