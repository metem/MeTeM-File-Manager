/*
*           Copyright 2012 by Mateusz Ucher
*
*              GNU GENERAL PUBLIC LICENSE
*                Version 3, 29 June 2007
*/

#include "directorytree.h"
#include "ui_directorytree.h"

DirectoryTree::DirectoryTree(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DirectoryTree),
    model(new QFileSystemModel())
{
    ui->setupUi(this);
    model->setFilter(QDir::Dirs | QDir::NoDotAndDotDot | QDir::Drives);
    model->setRootPath(QDir::rootPath());
    ui->tVDirs->setModel(model);

    ui->tVDirs->hideColumn(1);
    ui->tVDirs->hideColumn(2);
    ui->tVDirs->hideColumn(3);
}

DirectoryTree::~DirectoryTree()
{
    delete model;
    delete ui;
}

QDir DirectoryTree::GetSelectedDir()
{
    return QDir(*selectedDir);
}

void DirectoryTree::on_tVDirs_clicked(const QModelIndex &index)
{
    selectedDir = new QDir(model->fileInfo(index).absoluteFilePath());
}
