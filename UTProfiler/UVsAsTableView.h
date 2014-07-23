#ifndef UVSASTABLEVIEW_H
#define UVSASTABLEVIEW_H

#include <QDialog>

namespace Ui {
class UVsAsTableView;
}

class UVsAsTableView : public QDialog
{
    Q_OBJECT

public:
    explicit UVsAsTableView(QWidget *parent = 0);
    ~UVsAsTableView();

private:
    Ui::UVsAsTableView *ui;
};

#endif // UVSASTABLEVIEW_H
