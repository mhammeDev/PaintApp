#include "dialog.h"
#include "mainwindow.h"
#include "ui_dialog.h"
#include "paintwidgets.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->saveFile->setReadOnly(true);
    ui->saveFile->setText("/home/"+ui->projectName->text().trimmed()+".png");

    ui->widthSpinBox->setMaximum(1920);
    ui->heightSpinBox->setMaximum(1080);

    ui->widthSpinBox->setValue(500);
    ui->heightSpinBox->setValue(500);


}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_ButtonToChoose_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Choisir le dossier de sauvegarde"),
                                                       "/home",
                                                       QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

       if(dir.isEmpty()) {
           return; // Ne fais rien si aucun dossier n'a été sélectionné
       }

       QString nameFile = ui->projectName->text().trimmed();

       QString fullPath = dir + QDir::separator() + nameFile + ".png";
       ui->saveFile->setText(fullPath);

}


void Dialog::on_projectName_textChanged(const QString &arg1)
{
    if(arg1.isEmpty()){
        ui->projectName->setText("project");
        QMessageBox::warning(this, "Erreur", "Impossible de laisser ce champ vide");
        return;
    }
    ui->saveFile->setText("/home/"+ arg1 +".png");


}


void Dialog::on_cancelButton_clicked()
{
    MainWindow* mainWindow = MainWindow::getInstance();
        if (mainWindow) {
            this->close();
            mainWindow->show();
        }
}

void Dialog::on_createButton_clicked()

{

    int width = ui->widthSpinBox->value();

    int height = ui->heightSpinBox->value();



    PaintWidgets *paintWidget = new PaintWidgets(width, height, ui->saveFile->text()); // Passe la largeur et la hauteur

    paintWidget->setAttribute(Qt::WA_DeleteOnClose);

    hide();

    paintWidget->showMaximized();

}
