#ifndef PAINTWIDGETS_H
#define PAINTWIDGETS_H

#include <QMainWindow>
#include <QMenuBar>
#include <QPainter>
#include <QPixmap>
#include <QPoint>
#include <QMouseEvent>
#include <QFileDialog>
#include <QMessageBox>


namespace Ui {

class PaintWidgets;
}

class PaintWidgets : public QMainWindow
{
    Q_OBJECT

public:
    explicit PaintWidgets(int width = 500, int height = 500, const QString &filePath = QString(), const QImage& image = QImage(), QWidget *parent = nullptr);
    ~PaintWidgets();

public slots :
    void saveImage();
    void openFile();


  protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;


private slots:
    void on_actionSauvegarder_triggered();
    void on_actionOuvrir_triggered();

private:
    Ui::PaintWidgets *ui;
    QString filePath;
    bool drawing;
    QPixmap canvas;
    QPoint lastPoint;

};



#endif // PAINTWIDGETS_H
