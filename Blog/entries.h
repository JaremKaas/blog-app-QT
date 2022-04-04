#ifndef ENTRIES_H
#define ENTRIES_H

#include <QDialog>

namespace Ui {
class Entries;
}

class Entries : public QDialog
{
    Q_OBJECT
    QString authorEmail; //email
    QString authorID;

public:
    explicit Entries(QWidget *parent = nullptr, QString authorID="",QString authorEmail="");
    ~Entries();

private slots:
    void on_pushButton_delete_clicked();

private:
    Ui::Entries *ui;
};

#endif // ENTRIES_H
