#ifndef ADDENTRY_H
#define ADDENTRY_H

#include <QDialog>


namespace Ui {
class AddEntry;
}

class AddEntry : public QDialog
{
    Q_OBJECT
    int authorID;
    QString authorEmail;

public:
    explicit AddEntry(QWidget *parent = nullptr,int authorID=0,QString new_authorEmail="");
    ~AddEntry();
private slots:
    void on_pushButton_add_clicked();
private:
    Ui::AddEntry *ui;


};

#endif // ADDENTRY_H
