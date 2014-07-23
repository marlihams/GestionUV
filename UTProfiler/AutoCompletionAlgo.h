#ifndef AUTOCOMPLETIONALGO_H
#define AUTOCOMPLETIONALGO_H

#include <QDialog>

namespace Ui {
class AutoCompletionAlgo;
}

class AutoCompletionAlgo : public QDialog
{
    Q_OBJECT

public:
    explicit AutoCompletionAlgo(QWidget *parent = 0);
    ~AutoCompletionAlgo();

private:
    Ui::AutoCompletionAlgo *ui;
};

#endif // AUTOCOMPLETIONALGO_H
