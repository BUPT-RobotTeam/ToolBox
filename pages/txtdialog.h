#ifndef TXTDIALOG_H
#define TXTDIALOG_H

#include <QDialog>

namespace Ui {
class txtDialog;
}

class txtDialog : public QDialog
{
    Q_OBJECT

public:
    explicit txtDialog(QWidget *parent = nullptr);
    ~txtDialog();

//private:
    Ui::txtDialog *ui;
};

#endif // TXTDIALOG_H
