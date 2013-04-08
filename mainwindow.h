#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QFileSystemModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_treeView_clicked(const QModelIndex &index);

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_lEPath_textEdited(const QString &arg1);

private:
    Ui::MainWindow *ui;

    QFileSystemModel *dirsModel;
    QFileSystemModel *filesModel;
};

#endif // MAINWINDOW_H
