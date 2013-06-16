#include "aboutbox.h"
#include "ui_aboutbox.h"

AboutBox::AboutBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AboutBox)
{
    ui->setupUi(this);

    QFile file("COPYING.txt");
    if (file.open(QFile::ReadOnly | QFile::Text))
        ui->plainTextEdit->appendPlainText(file.readAll());
    else ui->plainTextEdit->appendPlainText("Can not load file.");
}

AboutBox::~AboutBox()
{
    delete ui;
}
