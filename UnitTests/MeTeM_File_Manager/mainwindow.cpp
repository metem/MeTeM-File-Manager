/*
*           Copyright 2013 by Mateusz Ucher
*
*              GNU GENERAL PUBLIC LICENSE
*                Version 3, 29 June 2007
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(bool createLog, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    dlg(NULL),
    createLogFile(createLog),
    logFile(NULL),
    logStream(NULL)
{
    if (createLogFile)
    {
        logFile = new QFile("log.txt");
        if (!logFile->open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
        {
            delete logFile;
            logFile = NULL;
            createLogFile = false;

            //msg can not open file
        }
        else
        {
            logStream = new QTextStream(logFile);
            writeLog("New log");
        }
    }

    ui->setupUi(this);

    for (int i = 0; i < 2; i++) //2 is number of models
    {
        filesModel[i] = new FileModel(this);
        filesModel[i]->setFilter(QDir::Dirs | QDir::Files | QDir::NoDot);
        filesModel[i]->setRootPath(QDir::rootPath()); //root path (for unix based '/')
    }
    ui->filesExplorerView->setModel(filesModel[0]);
    ui->filesExplorerView_2->setModel(filesModel[1]);

    ui->chartDockWidget_1->setModel(filesModel[0]);
    ui->chartDockWidget_2->setModel(filesModel[1]);

    //Shortcuts
    scOpen = new QShortcut(QKeySequence("F3"), this);
    scMove = new QShortcut(QKeySequence("F6"), this);
    scCopy = new QShortcut(QKeySequence("F5"), this);
    scRemove = new QShortcut(QKeySequence("F8"), this);
    scRename = new QShortcut(QKeySequence("F9"), this);
    scMkdir = new QShortcut(QKeySequence("F7"), this);
    scCompare = new QShortcut(QKeySequence("F4"), this);
    scExit = new QShortcut(QKeySequence("F10"), this);

    connect(scOpen, SIGNAL(activated()), this, SLOT(on_pbOpen_clicked()));
    connect(scMove, SIGNAL(activated()), this, SLOT(on_pbMove_clicked()));
    connect(scCopy, SIGNAL(activated()), this, SLOT(on_pbCopy_clicked()));
    connect(scRemove, SIGNAL(activated()), this, SLOT(on_pbRemove_clicked()));
    connect(scRename, SIGNAL(activated()), this, SLOT(on_pbRename_clicked()));
    connect(scMkdir, SIGNAL(activated()), this, SLOT(on_pbMkdir_clicked()));
    connect(scCompare, SIGNAL(activated()), this, SLOT(on_pbCompare_clicked()));
    connect(scExit, SIGNAL(activated()), this, SLOT(close()));

    ui->filesExplorerView->installEventFilter(this);
    ui->filesExplorerView_2->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    if ((logFile != NULL) && (logFile->isOpen())) logFile->close();
    delete scOpen;
    delete scMove;
    delete scCopy;
    delete scRemove;
    delete scRename;
    delete scMkdir;
    delete scCompare;
    delete scExit;

    delete dlg;
    delete logStream;
    delete logFile;

    delete ui;
}


//get focused window (for actions like mkdir etc...)
bool MainWindow::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::FocusIn)
    {
        if (object == ui->filesExplorerView) lastFocus = 0;
        else if (object == ui->filesExplorerView_2) lastFocus = 1;
    }
    return false;
}

void MainWindow::writeLog(const QString log)
{
    if (createLogFile)
    {
        try
        {
            QDateTime now = QDateTime::currentDateTime();
            *logStream << now.toString("dd/MM/yyyy hh:mm") << " - " << log << "\r\n";
        }
        catch(...)
        {
            qDebug() << "Can't write to file stream";
        }
    }
}

void MainWindow::traceTo(const QModelIndex &index, int explorerID)
{
    QFileInfo file = filesModel[explorerID]->fileInfo(index);
    QString path = file.absoluteFilePath();

#ifdef Q_OS_UNIX
    if (path == "/..") path = "";
#endif

    if (file.isReadable())
    {
        if (file.isDir())
        {
            if (explorerID == 0)
            {
                ui->filesExplorerView->setRootIndex(filesModel[0]->setRootPath(path));
                ui->lEPath->setText(path);
            }
            else
            {
                ui->filesExplorerView_2->setRootIndex(filesModel[1]->setRootPath(path));
                ui->lEPath_2->setText(path);
            }
        }
        else QDesktopServices::openUrl(QUrl::fromLocalFile(path));
    }
    else
    {
        // msg -> can't read file
    }
}

QModelIndexList MainWindow::getSelectedRowsIndexes(int explorerID)
{
    QModelIndexList indexes;

    if (explorerID == 0) indexes = ui->filesExplorerView->selectionModel()->selectedRows();
    else indexes = ui->filesExplorerView_2->selectionModel()->selectedRows();

    return indexes;
}

void MainWindow::on_filesExplorerView_doubleClicked(const QModelIndex &index)
{
    traceTo(index, 0);
}

void MainWindow::on_filesExplorerView_2_doubleClicked(const QModelIndex &index)
{
    traceTo(index, 1);
}

void MainWindow::on_lEPath_returnPressed()
{
    ui->filesExplorerView->setRootIndex(filesModel[0]->setRootPath(ui->lEPath->text()));
}


void MainWindow::on_lEPath_2_returnPressed()
{
    ui->filesExplorerView_2->setRootIndex(filesModel[1]->setRootPath(ui->lEPath_2->text()));
}

void MainWindow::on_pbOpen_clicked()
{
    QModelIndexList indexes = getSelectedRowsIndexes(lastFocus);

    for (int i = 0; i < indexes.count(); ++i)
    {
        QString file = filesModel[lastFocus]->fileInfo(indexes[i]).absoluteFilePath();
        QDesktopServices::openUrl(QUrl::fromLocalFile(file));
        writeLog("Opening " + file);
    }
}

void MainWindow::on_pbMove_clicked()
{
    //TODO: Move to other thread and make copy/move dialog.

    QModelIndexList indexes = getSelectedRowsIndexes(lastFocus);
    QString destination;
    if (lastFocus == 0) destination = filesModel[1]->rootPath();
    else destination = filesModel[0]->rootPath();

    destination += "/";

    QFileInfo file;
    for (int i = 0; i < indexes.count(); ++i)
    {
        file = filesModel[lastFocus]->fileInfo(indexes[i]).absoluteFilePath();
        if (!QFile::rename(file.absoluteFilePath(), destination + file.fileName()))
        {
            writeLog("Can't move file from " + file.absoluteFilePath() + " to " + destination + file.fileName());
        }
        else writeLog("Moving file from " + file.absoluteFilePath() + " to " + destination + file.fileName());
    }
}

void MainWindow::on_pbCopy_clicked()
{
    //TODO: Move to other thread and make copy/move dialog.

    QModelIndexList indexes = getSelectedRowsIndexes(lastFocus);
    QString destination;
    if (lastFocus == 0) destination = filesModel[1]->rootPath();
    else destination = filesModel[0]->rootPath();

    destination += "/";

    QFileInfo file;
    for (int i = 0; i < indexes.count(); ++i)
    {
        file = filesModel[lastFocus]->fileInfo(indexes[i]).absoluteFilePath();
        if (!QFile::copy(file.absoluteFilePath(), destination + file.fileName()))
        {
            writeLog("Can't copy file from " + file.absoluteFilePath() + " to " + destination + file.fileName());
        }
        else writeLog("Copying file from " + file.absoluteFilePath() + " to " + destination + file.fileName());
    }
}

void MainWindow::on_pbRemove_clicked()
{
    QMessageBox msgBox;
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);

    QModelIndexList indexes = getSelectedRowsIndexes(lastFocus);

    msgBox.setWindowTitle("Remove");
    msgBox.setText(QString("Are you sure you want to delete %1 file(s)?").arg(indexes.count()));

    QFileInfo file;
    if(msgBox.exec() == QMessageBox::Yes)
        for (int i = 0; i < indexes.count(); ++i)
        {
            file = filesModel[lastFocus]->fileInfo(indexes[i]).absoluteFilePath();
            if (!QFile::remove(file.absoluteFilePath()))
            {
                writeLog("Can't remove " + file.absoluteFilePath());
            }
            else writeLog("Removing " + file.absoluteFilePath());
        }
}

void MainWindow::on_pbRename_clicked()
{
    QModelIndexList indexes = getSelectedRowsIndexes(lastFocus);

    if (indexes.count() == 1)
    {
        QFileInfo file = filesModel[lastFocus]->fileInfo(indexes[0]).absoluteFilePath();

        bool ok;
        QString newName = QInputDialog::getText(this, tr("Rename"),
                                                tr("New name:"), QLineEdit::Normal,
                                                file.fileName(), &ok);
        if (ok && !newName.isEmpty())
        {
            if (!QFile::rename(file.absoluteFilePath(), file.path() + '/' + newName))
            {
                writeLog("Can't rename " + file.absoluteFilePath());
            }
            else writeLog("Renaming " + file.absoluteFilePath() + " > " + newName);
        }
    }
    else
    {
        //open multi-rename tool
    }
}

void MainWindow::on_pbCompare_clicked()
{
    QModelIndexList indexes[2] =
    {
        ui->filesExplorerView->selectionModel()->selectedRows(),
        ui->filesExplorerView_2->selectionModel()->selectedRows()
    };

    if ((indexes[0].count() == 1) && (indexes[1].count() == 1))
    {
        delete dlg;
        dlg = new ComparatorDialog(filesModel[0]->fileInfo(indexes[0][0]),filesModel[1]->fileInfo(indexes[1][0]),this);
        dlg->show();
        writeLog("Comparing " + filesModel[0]->fileInfo(indexes[0][0]).absoluteFilePath() + " with " + filesModel[1]->fileInfo(indexes[1][0]).absoluteFilePath());
    }
}

void MainWindow::on_pbMkdir_clicked()
{
    QDir dir = filesModel[lastFocus]->rootPath();

    bool ok;

    QString dirName = QInputDialog::getText(this, tr("Make directory"),
                                            tr("Directory name:"), QLineEdit::Normal,
                                            "", &ok);
    if (ok && !dirName.isEmpty())
    {
        if (!dir.mkdir(dirName))
        {
            writeLog("Can't make dir: " + dirName);
        }
        else writeLog("Creating dir: " + dirName);
    }
}

void MainWindow::on_tbDuplicates_1_clicked()
{
    FinderDialog::getInstance().Duplicates(true);
    FinderDialog::getInstance().SetPath(ui->lEPath->text());
    FinderDialog::getInstance().show();
}

void MainWindow::on_tbDuplicates_2_clicked()
{
    FinderDialog::getInstance().Duplicates(true);
    FinderDialog::getInstance().SetPath(ui->lEPath_2->text());
    FinderDialog::getInstance().show();
}

void MainWindow::on_tb_Finder_1_clicked()
{
    FinderDialog::getInstance().Duplicates(false);
    FinderDialog::getInstance().SetPath(ui->lEPath->text());
    FinderDialog::getInstance().show();
}

void MainWindow::on_tb_Finder_2_clicked()
{
    FinderDialog::getInstance().Duplicates(false);
    FinderDialog::getInstance().SetPath(ui->lEPath_2->text());
    FinderDialog::getInstance().show();
}

void MainWindow::on_pbAbout_clicked()
{
    AboutBox::getInstance().show();
}
