/*
*           Copyright 2013 by Mateusz Ucher
*
*              GNU GENERAL PUBLIC LICENSE
*                Version 3, 29 June 2007
*/

#include "comparatordialog.h"
#include "ui_comparatordialog.h"

ComparatorDialog::ComparatorDialog(QFileInfo file1, QFileInfo file2, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ComparatorDialog)
{
    ui->setupUi(this);

    ui->gbFile1->setTitle(file1.fileName());
    ui->l_created_1->setText(file1.created().toString("dd/MM/yyyy hh:mm"));
    ui->l_mod_1->setText(file1.lastModified().toString("dd/MM/yyyy hh:mm"));
    ui->l_read_1->setText(file1.lastRead().toString("dd/MM/yyyy hh:mm"));
    ui->l_size_1->setText(TextFormatter<qint64>::SizeFromBytes(file1.size()));

    ui->gbFile2->setTitle(file2.fileName());
    ui->l_created_2->setText(file2.created().toString("dd/MM/yyyy hh:mm"));
    ui->l_mod_2->setText(file2.lastModified().toString("dd/MM/yyyy hh:mm"));
    ui->l_read_2->setText(file2.lastRead().toString("dd/MM/yyyy hh:mm"));
    ui->l_size_2->setText(TextFormatter<qint64>::SizeFromBytes(file2.size()));

    QFont boldF;
    boldF.setBold(true);

    if (file1.created() > file2.created()) ui->l_created_1->setFont(boldF);
    else ui->l_created_2->setFont(boldF);

    if (file1.lastModified() > file2.lastModified()) ui->l_mod_1->setFont(boldF);
    else ui->l_mod_2->setFont(boldF);

    if (file1.lastRead() > file2.lastRead()) ui->l_read_1->setFont(boldF);
    else ui->l_read_2->setFont(boldF);

    if (file1.size() > file2.size()) ui->l_size_1->setFont(boldF);
    else ui->l_size_2->setFont(boldF);
}

ComparatorDialog::~ComparatorDialog()
{
    delete ui;
}
