#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMenu>
#include <QTreeWidgetItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::WindowStaysOnTopHint);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_treeWidget_customContextMenuRequested(const QPoint &pos)
{
    QMenu menu(this);

    menu.addAction(ui->actionAdd_Task);
    menu.addAction(ui->actionRemove_Task);

    menu.exec(ui->treeWidget->mapToGlobal(pos));
}

void MainWindow::on_actionAdd_Task_triggered()
{
    QPoint globalPos = QCursor::pos();
    QPoint localPos = ui->treeWidget->viewport()->mapFromGlobal(globalPos);

    QTreeWidgetItem *item = ui->treeWidget->itemAt(localPos);

    QTreeWidgetItem *newItem = new QTreeWidgetItem();
    newItem->setFlags(Qt::ItemIsDragEnabled |
                      Qt::ItemIsDropEnabled |
                      Qt::ItemIsEditable |
                      Qt::ItemIsEnabled |
                      Qt::ItemIsSelectable);

    if (item == nullptr)
    {
        ui->treeWidget->addTopLevelItem(newItem);
    }
    else
    {
        item->addChild(newItem);
    }
}

void MainWindow::on_actionRemove_Task_triggered()
{

}

void MainWindow::on_treeWidget_itemChanged(QTreeWidgetItem *item, int column)
{

}
