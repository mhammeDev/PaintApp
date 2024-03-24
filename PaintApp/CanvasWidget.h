#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>

class CanvasWidget : public QWidget {
public:
    CanvasWidget(const QPixmap& pixmap, QWidget *parent = nullptr) : QWidget(parent), pixmap(pixmap) {}

protected:
    void paintEvent(QPaintEvent *event) override {
        QPainter painter(this);
        painter.drawPixmap(0, 0, pixmap);
    }

private:
    QPixmap pixmap;
};

// Utilisez cette classe pour créer un widget et définissez-le comme contenu de la zone de défilement
CanvasWidget *canvasWidget = new CanvasWidget(canvas);
scrollArea->setWidget(canvasWidget);

#endif // CANVASWIDGET_H
