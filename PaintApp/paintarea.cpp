#include "paintarea.h"

PaintArea::PaintArea(int drawableWidth, int drawableHeight, QWidget *parent)
    : QWidget(parent), drawableWidth(drawableWidth), drawableHeight(drawableHeight) {
    // Ajuste la taille du widget pour correspondre à la zone dessinable, plus une marge
    setFixedSize(drawableWidth + 10, drawableHeight + 10);
}

void PaintArea::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    // Dessine un cadre autour de la zone dessinable
    painter.drawRect(5, 5, drawableWidth, drawableHeight);

}
