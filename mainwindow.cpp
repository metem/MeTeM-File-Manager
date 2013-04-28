#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //set initial size
    QList<int> sizes;
    sizes << 150 << 1;
    ui->splitter->setSizes(sizes);
    ui->splitter->setStretchFactor(0, 0);
    ui->splitter->setStretchFactor(1, 1);

    dirsModel = new QFileSystemModel(this);
    dirsModel->setFilter(QDir::Dirs | QDir::NoDotAndDotDot | QDir::Drives);
    dirsModel->setRootPath(QDir::rootPath());
    ui->treeView->setModel(dirsModel);

    filesModel = new QFileSystemModel(this);
    filesModel->setFilter(QDir::Dirs | QDir::Files | QDir::NoDot);
    filesModel->setRootPath(QDir::rootPath());
    ui->tableView->setModel(filesModel);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    QFileInfo file(dirsModel->fileInfo(index).absoluteFilePath());
    ui->tableView->setRootIndex(filesModel->setRootPath(file.filePath()));

    ui->lEPath->setText(file.filePath());
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    QFileInfo file(dirsModel->fileInfo(index).absoluteFilePath());
    ui->tableView->setRootIndex(filesModel->setRootPath(file.filePath()));

    ui->lEPath->setText(file.filePath());

    ui->treeView->scrollTo(dirsModel->setRootPath(file.filePath()));
}

void MainWindow::on_lEPath_textEdited(const QString &arg1)
{
    ui->treeView->scrollTo(dirsModel->setRootPath(arg1));
    ui->tableView->setRootIndex(filesModel->setRootPath(arg1));
}
