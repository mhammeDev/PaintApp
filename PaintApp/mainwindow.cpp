#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"

MainWindow* MainWindow::instance = nullptr;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    instance = this;

}

MainWindow::~MainWindow()
{
    delete ui;
}

MainWindow* MainWindow::getInstance() {
    return instance;
}


void MainWindow::on_CreateButton_clicked()
{
    Dialog dialog;
    dialog.setModal(true);
    hide();
    dialog.exec();

}

void MainWindow::on_OpenButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open a file","/home/");
    // Now I can get my file with fileName
}

