#include "paintwidget.h"
#include "ui_paintwidget.h"

PaintWidget::PaintWidget(int width, int height, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PaintWidget)
{
    setDrawableAreaSize(width, height);
    ui->setupUi(this);
    setWindowTitle(tr("Paint"));

}

PaintWidget::~PaintWidget()
{
    delete ui;
}

void PaintWidget::resizeEvent(QResizeEvent *event) {
    // Réajuste la position de la zone dessinable en la centrant
    setDrawableAreaSize(drawableArea.width(), drawableArea.height());
}

void PaintWidget::setDrawableAreaSize(int width, int height) {
        // Centre la zone dessinable
    int x = (this->width() - width) / 2;
    int y = (this->height() - height) / 2;
    drawableArea = QRect(x, y, width, height);
    update(); // Demande de redessiner le widget
}

void PaintWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.fillRect(this->rect(), Qt::lightGray); // Fond gris pour tout le widget
    painter.fillRect(drawableArea, Qt::white); // Zone dessinable en blanc

    // Dessine quelque chose dans la zone dessinable si nécessaire
    // Utilise `drawableArea` comme référence pour le dessin
}

