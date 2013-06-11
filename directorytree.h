#ifndef DIRECTORYTREE_H
#define DIRECTORYTREE_H

/*
*           Copyright 2012 by Mateusz Ucher
*
*              GNU GENERAL PUBLIC LICENSE
*                Version 3, 29 June 2007
*/

#include <QDialog>
#include <QFileSystemModel>
#include <QTreeView>

namespace Ui {
class DirectoryTree;
}

//! Dialog for dir choose
class DirectoryTree : public QDialog
{
    Q_OBJECT
    
public:
    explicit DirectoryTree(QWidget *parent = 0);
    ~DirectoryTree();

    QDir GetSelectedDir();
    
private slots:
    void on_tVDirs_clicked(const QModelIndex &index);

private:
    Ui::DirectoryTree *ui;
    QFileSystemModel *model;
    QDir *selectedDir;
};

#endif // DIRECTORYTREE_H
