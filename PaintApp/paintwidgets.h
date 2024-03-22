#ifndef PAINTWIDGETS_H
#define PAINTWIDGETS_H

#include <QMainWindow>
#include <QPainter>
#include <QMenuBar>


namespace Ui {
class PaintWidgets;
}

class PaintWidgets : public QMainWindow
{
    Q_OBJECT

public:
    explicit PaintWidgets(int width = 500, int height = 500,QWidget *parent = nullptr);
    ~PaintWidgets();

    void setDrawableAreaSize(int width, int height);

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    Ui::PaintWidgets *ui;
    QRect drawableArea;
    QMenuBar *menuBar;
};

#endif // PAINTWIDGETS_H
