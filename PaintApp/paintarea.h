#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QWidget>
#include <QPainter>

class PaintArea : public QWidget {
    Q_OBJECT

public:
    explicit PaintArea(int drawableWidth, int drawableHeight, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int drawableWidth, drawableHeight;
};

#endif // PAINTAREA_H
