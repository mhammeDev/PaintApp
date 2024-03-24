#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include "paintwidgets.h"


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
    QString fileName = QFileDialog::getOpenFileName(this, tr("Ouvrir un fichier"), QDir::homePath(), tr("Images (*.png *.jpeg *.jpg)"));
    if (!fileName.isEmpty()) {
        QImage image;
        if (image.load(fileName)) {
            PaintWidgets *paintWidget = new PaintWidgets(image.width(), image.height(), fileName,image);

            paintWidget->setAttribute(Qt::WA_DeleteOnClose);

            hide();

            paintWidget->showMaximized();


        } else {
            QMessageBox::warning(this, tr("Ouvrir un fichier"), tr("Le fichier n'a pas pu être ouvert."));
        }
    }
}

