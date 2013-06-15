#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/*
*           Copyright 2012 by Mateusz Ucher
*
*              GNU GENERAL PUBLIC LICENSE
*                Version 3, 29 June 2007
*/

#include <QMainWindow>
#include <QtCore>
#include <QDesktopServices>
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
    //! Constructor
    /*!
     * \param createLog if true creating log.txt file in application directory (param -l)
     */
    explicit MainWindow(bool createLog, QWidget *parent = 0);
    ~MainWindow();

    //! Used for browse dirs and open files
    /*!
     * index is selected index returned by QTableView
     * explorerID is ID of FileModel to use
     */
    void traceTo(const QModelIndex &index, int explorerID);

    //! returns all selected indexes from specified FileModel
    /*!
     * \return returns all selected indexes from specified FileModel
     */
    QModelIndexList getSelectedRowsIndexes(int explorerID);
    
public slots:
    //! Used to write log in format "date + time + log"
    void writeLog(const QString log);

private slots:
    void on_filesExplorerView_doubleClicked(const QModelIndex &index);

    void on_lEPath_returnPressed();

    void on_filesExplorerView_2_doubleClicked(const QModelIndex &index);

    void on_lEPath_2_returnPressed();

    void on_pbOpen_clicked();

    void on_pbMove_clicked();

    void on_pbCopy_clicked();

    void on_pbRemove_clicked();

    void on_pbRename_clicked();

    void on_pbMkdir_clicked();

    void on_tbDuplicates_1_clicked();

    void on_tbDuplicates_2_clicked();

    void on_pbCompare_clicked();

    void on_tb_Finder_1_clicked();

    void on_tb_Finder_2_clicked();

private:
    //! used to figure out which file explorer is currently focused
    bool eventFilter(QObject *object, QEvent *event);

    Ui::MainWindow *ui;
    FileModel *filesModel[2];
    int lastFocus;
    ComparatorDialog *dlg;

    bool createLogFile;

    QFile *logFile;
    QTextStream *logStream;

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
