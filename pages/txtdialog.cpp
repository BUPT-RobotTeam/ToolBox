#include "txtdialog.h"
#include "ui_txtdialog.h"

txtDialog::txtDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::txtDialog)
{
    ui->setupUi(this);
}

txtDialog::~txtDialog()
{
    delete ui;
}
