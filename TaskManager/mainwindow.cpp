#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <treemodel.h>
#include <task.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_model(new TreeModel(this))
{
    ui->setupUi(this);
    ui->treeView->setModel(m_model);

    this->setWindowFlags(Qt::WindowStaysOnTopHint);

    m_model->insertColumn(0);
    m_model->setHeaderData(0, Qt::Horizontal, "Name");
}

MainWindow::~MainWindow()
{

}

void MainWindow::on_actionAdd_Task_triggered()
{
    QModelIndex idx = ui->treeView->indexAt(m_actionPos);

    m_model->insertRows(0, 1, idx);
}

void MainWindow::on_actionRemove_Task_triggered()
{

}

void MainWindow::on_savePushButton_clicked()
{
}

void MainWindow::on_treeView_customContextMenuRequested(const QPoint &pos)
{
    QMenu menu(this);

    menu.addAction(ui->actionAdd_Task);
    menu.addAction(ui->actionRemove_Task);

    m_actionPos = pos;
    menu.exec(ui->treeView->viewport()->mapToGlobal(pos));
}
