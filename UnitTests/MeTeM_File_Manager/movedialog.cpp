#include "movedialog.h"
#include "ui_movedialog.h"

MoveDialog::MoveDialog(QFileInfoList *fileList, QDir *destinationDir, bool deleteAfter, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MoveDialog),
    fileCopierThread(new QThread()),
    fileCopier(new FilesCopier())
{
    ui->setupUi(this);

    if (deleteAfter)
        this->setWindowTitle("Moving");
    else
        this->setWindowTitle("Copying");

    fileCopier->setSourceFileList(fileList);
    fileCopier->setDestinatonDir(destinationDir);
    fileCopier->setDeleteAfter(deleteAfter);

    //thread settings
    fileCopier->moveToThread(fileCopierThread);
    connect(fileCopier, SIGNAL(nextFile(QString)), ui->lFile, SLOT(setText(QString)));
    connect(fileCopier, SIGNAL(addToLog(QString)), this, SLOT(addToLog(QString)));
    connect(fileCopier, SIGNAL(progressChanged(int)), ui->pB_Progress, SLOT(setValue(int)));
    connect(fileCopierThread, SIGNAL(started()), fileCopier, SLOT(copy()));
    connect(fileCopier, SIGNAL(finished()), fileCopierThread, SLOT(quit()), Qt::DirectConnection);
    connect(fileCopier, SIGNAL(finished()), this, SLOT(finished()));

    fileCopierThread->start();
}

MoveDialog::~MoveDialog()
{
    fileCopierThread->terminate();

    delete fileCopierThread;
    delete fileCopier;

    delete ui;
}

void MoveDialog::addToLog(QString value)
{
    ui->lWlog->addItem(value);
    ui->lWlog->scrollToBottom();
}

void MoveDialog::closeEvent(QCloseEvent *event)
{
    fileCopier->abort();
    fileCopier->thread()->wait();
    event->accept();
}

void MoveDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    (void)button;
    this->close();
}

void MoveDialog::finished()
{
    ui->pB_Progress->setValue(100);
    ui->lFile->setText("finished");
}
