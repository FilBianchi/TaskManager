#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class TreeModel;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_actionAdd_Task_triggered();

    void on_actionRemove_Task_triggered();

    void on_savePushButton_clicked();

    void on_treeView_customContextMenuRequested(const QPoint &pos);

private:

    QPoint m_actionPos;

    Ui::MainWindow *ui;
    TreeModel *m_model;

};
#endif // MAINWINDOW_H
