#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    static MainWindow* instance;
    static MainWindow* getInstance();

private slots:
    void on_CreateButton_clicked();

    void on_OpenButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
