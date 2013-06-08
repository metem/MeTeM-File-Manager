#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/*-------------------------------------------------------
         Copyright - GNU GENERAL PUBLIC LICENSE
                Version 3, 29 June 2007

Main Window Class

METHODS:
    void traceTo(const QModelIndex &index, int explorerID);

    Used for browse dirs and open files
    index is selected index returned by QTableView
    explorerID is ID of FileModel to use


    QModelIndexList getSelectedRowsIndexes(int explorerID);

    returns all selected indexes from specified FileModel

ADDITIONAL INFO:


TODO:
-

---------------------------------------------------------*/

#include <QMainWindow>
#include <QtCore>
#include <QDesktopServices>
#include <QMessageBox>
#include <QInputDialog>
#include <QShortcut>

#include "comparatordialog.h"
#include "finderdialog.h"
#include "filemodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void traceTo(const QModelIndex &index, int explorerID);
    QModelIndexList getSelectedRowsIndexes(int explorerID);
    
private slots:
    void on_filesExplorerView_doubleClicked(const QModelIndex &index);

    void on_lEPath_returnPressed();

    void on_filesExplorerView_2_doubleClicked(const QModelIndex &index);

    void on_lEPath_2_returnPressed();

    void on_pbOpen_clicked();

    void on_filesExplorerView_activated(const QModelIndex &index);

    void on_filesExplorerView_2_activated(const QModelIndex &index);

    void on_pbMove_clicked();

    void on_pbCopy_clicked();

    void on_pbRemove_clicked();

    void on_pbRename_clicked();

    void on_pbMkdir_clicked();

    void on_tbDuplicates_1_clicked();

    void on_tbDuplicates_2_clicked();

    void on_pbCompare_clicked();

private:
    Ui::MainWindow *ui;
    FileModel *filesModel[2];
    int lastFocus;
    ComparatorDialog *dlg;


    //Shortcut
    QShortcut *scOpen;
    QShortcut *scMove;
    QShortcut *scCopy;
    QShortcut *scRemove;
    QShortcut *scRename;
    QShortcut *scMkdir;
    QShortcut *scCompare;
    QShortcut *scExit;
};

#endif // MAINWINDOW_H
