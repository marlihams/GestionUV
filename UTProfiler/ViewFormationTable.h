#ifndef VIEWFORMATIONTABLE_H
#define VIEWFORMATIONTABLE_H

#include <QDialog>

namespace Ui {
class ViewFormationTable;
}

class ViewFormationTable : public QDialog
{
    Q_OBJECT

public:
    explicit ViewFormationTable(QWidget *parent = 0);
    ~ViewFormationTable();

private:
    Ui::ViewFormationTable *ui;
};

#endif // VIEWFORMATIONTABLE_H
