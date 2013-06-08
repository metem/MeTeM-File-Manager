#include "comparatordialog.h"
#include "ui_comparatordialog.h"

ComparatorDialog::ComparatorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ComparatorDialog)
{
    ui->setupUi(this);
}

ComparatorDialog::~ComparatorDialog()
{
    delete ui;
}
