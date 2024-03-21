#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>


namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:

    void on_ButtonToChoose_clicked();

    void on_projectName_textChanged(const QString &arg1);

    void on_cancelButton_clicked();

    void on_createButton_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
