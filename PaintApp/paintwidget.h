#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QDialog>
#include <QPainter>
#include <QMenuBar>



namespace Ui {
class PaintWidget;
}

class PaintWidget : public QDialog
{
    Q_OBJECT

public:
    explicit PaintWidget(int width = 400, int height = 300,QWidget *parent = nullptr);
    ~PaintWidget();

    void setDrawableAreaSize(int width, int height);

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;


private:
    Ui::PaintWidget *ui;
    QRect drawableArea;
    QMenuBar *menuBar;


};

#endif // PAINTWIDGET_H
