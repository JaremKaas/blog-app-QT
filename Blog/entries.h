#ifndef ENTRIES_H
#define ENTRIES_H

#include <QDialog>

namespace Ui {
class Entries;
}

class Entries : public QDialog
{
    Q_OBJECT
    QString authorID;

public:
    explicit Entries(QWidget *parent = nullptr, QString authorID=0);
    ~Entries();

private:
    Ui::Entries *ui;
};

#endif // ENTRIES_H
