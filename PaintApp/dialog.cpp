#include "dialog.h"
#include "mainwindow.h"
#include "ui_dialog.h"
#include "paintwidgets.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    baseDir = QDir::homePath() + "/";

    ui->setupUi(this);
    ui->saveFile->setReadOnly(true);
    ui->saveFile->setText(baseDir+ui->projectName->text().trimmed()+ui->comboBox->currentText());

    ui->widthSpinBox->setMaximum(2000);
    ui->heightSpinBox->setMaximum(2000);

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
                                                       QDir::homePath(),
                                                       QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

       if(dir.isEmpty()) {
           return;
       }

       baseDir = dir + "/";

       QString nameFile = ui->projectName->text().trimmed();

       QString fullPath = baseDir + nameFile + ui->comboBox->currentText();
       ui->saveFile->setText(fullPath);

}


void Dialog::on_projectName_textChanged(const QString &arg1)
{
    QString selectedFormat = ui->comboBox->currentText();
    ui->saveFile->setText(baseDir+ arg1 +selectedFormat);


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

    if(ui->projectName->text().isEmpty()){
        ui->projectName->setText("project");
        QMessageBox::warning(this, "Erreur", "Impossible de laisser le champ nom vide");
        return;
    }

    int width = ui->widthSpinBox->value();

    int height = ui->heightSpinBox->value();



    PaintWidgets *paintWidget = new PaintWidgets(width, height, ui->saveFile->text()); // Passe la largeur et la hauteur

    paintWidget->setAttribute(Qt::WA_DeleteOnClose);

    hide();

    paintWidget->showMaximized();

}

void Dialog::on_comboBox_activated(const QString &arg1)
{
    QString currentPath = ui->saveFile->text();
     int lastDotIndex = currentPath.lastIndexOf('.');
     if(lastDotIndex != -1) {
         currentPath = currentPath.left(lastDotIndex);
     }

     ui->saveFile->setText(currentPath + arg1);

}

