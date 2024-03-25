#include "paintwidgets.h"
#include "ui_paintwidgets.h"
#include "drawingcommand.h"
#include "dialog.h"




PaintWidgets::PaintWidgets(int width, int height, const QString &filePath, const QImage& image,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PaintWidgets),
    filePath(filePath),
    drawing(false),
    currentTool(Pen),
    currentColor(Qt::black),
    intensity(5),
    saveChange(false)

{

    ui->setupUi(this);
    setWindowTitle(tr("Paint"));
    canvas = QPixmap(width+30, height);


    colorPickerAction = ui->toolBar->addAction(createColorIcon(currentColor), "");
    ui->toolBar->setIconSize(QSize(30,30));

    connect(colorPickerAction, &QAction::triggered, this, &PaintWidgets::onColorPickerClicked);
    currentCheck = ui->pen;
    currentCheck->setChecked(true);
    intensitySlider = new QSlider(Qt::Horizontal, this);
    intensitySlider->setMinimum(1);
    intensitySlider->setMaximum(20);
    intensitySlider->setValue(intensity);
    ui->toolBar->addWidget(intensitySlider);

    updateCursorForDrawing();



    connect(intensitySlider, &QSlider::valueChanged, this, &PaintWidgets::setIntensity);

    if (image.isNull()) {
            canvas.fill(Qt::white);
    } else{
        canvas = QPixmap::fromImage(image);
        update();
        this->resize(canvas.size());
    }




    setFixedSize(width, height);
}



PaintWidgets::~PaintWidgets()
{
    delete ui;
}



void PaintWidgets::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        lastPoint = event->pos();
        currentPoint= event->pos();
        drawing = true;
        QPainter painter(&canvas);
        switch (currentTool) {
            case Pen:
                saveChange=false;
                painter.setPen(QPen(currentColor, intensity, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
                painter.drawPoint(lastPoint);
                break;
            case Eraser:
                saveChange=false;
                painter.setPen(QPen(Qt::white, intensity, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
                painter.drawPoint(lastPoint);
                break;
            case Bucket:
                saveChange=false;
                floodFill(lastPoint,currentColor, painter);
                drawing = false;
                break;
             case Pipet:
                currentColor = canvas.toImage().pixelColor(lastPoint);
                colorPickerAction->setIcon(createColorIcon(currentColor));
                drawing = false;
                break;
             case Line:
                drawing=true;
                break;
              case Rectangle:
                drawing= true;
                break;
              case Ellipse:
                drawing = true;
                break;
              case ColorPicker:
                break;
              case Loupe:
                QPoint mousePos = event->pos();
                applyZoom(1.1, mousePos);
                break;
        }
        painter.end();
        initialState = canvas;
        update();
    } else if(event->button() == Qt::RightButton && currentTool==Loupe){
        QPoint mousePos = event->pos();
        applyZoom(0.909, mousePos);
        update();
    }

}



void PaintWidgets::mouseMoveEvent(QMouseEvent *event) {

    if ((event->buttons() & Qt::LeftButton) && drawing) {
        QPainter painter(&canvas);
        switch (currentTool) {
            case Pen:
                saveChange=false;
                painter.setPen(QPen(currentColor, intensity, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
                painter.drawLine(lastPoint, event->pos());
                lastPoint=event->pos();
                break;
             case Eraser:
                saveChange=false;
                painter.setPen(QPen(Qt::white, intensity, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
                painter.drawLine(lastPoint, event->pos());
                lastPoint=event->pos();
                break;
             case Bucket:
                break;
             case Pipet:
                break;
             case Line :
                currentPoint = event->pos();
                break;
             case Rectangle:
                currentPoint = event->pos();
                break;
            case Ellipse:
            currentPoint = event->pos();
                break;
             case Loupe:
                break;
            case ColorPicker:
                break;

        }

        update();
    }

}



void PaintWidgets::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && drawing) {
        QPainter painter(&canvas);
                painter.setPen(QPen(currentColor, intensity, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
                QRect rect(lastPoint, event->pos());
                switch (currentTool) {
                case Pen:
                    break;
                case Eraser:
                    break;
                case Bucket:
                    break;
                case Pipet:
                    break;
                case Line:
                    saveChange=false;
                    painter.setPen(QPen(currentColor, intensity, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
                    painter.drawLine(lastPoint, event->pos());
                    drawing=false;
                    break;
                case Rectangle:
                    saveChange=false;
                    painter.drawRect(rect);
                    break;
                case Ellipse:
                    saveChange=false;
                    painter.drawEllipse(rect);
                    break;
                case Loupe:
                    break;
                case ColorPicker:
                  break;

                }
                lastPoint=event->pos();
                painter.end();
                update();
                finalState = canvas;
                undoStack.push(new DrawingCommand(initialState, finalState, [this](const QPixmap& state) {
                    canvas = state;
                    update();
                }));


    }
}

void PaintWidgets::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRectF destinationRect(contentOffset.x(), contentOffset.y(), canvas.width() * zoomLevel, canvas.height() * zoomLevel);
    painter.drawPixmap(destinationRect, canvas, canvas.rect());

    if (drawing && (currentTool == Line || currentTool == Rectangle || currentTool == Ellipse)) {
          painter.setPen(QPen(currentColor, intensity, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

          if (currentTool == Line) {
              painter.drawLine(lastPoint, currentPoint);
          } else if (currentTool == Rectangle) {
              QRect rect(lastPoint, currentPoint);
              painter.drawRect(rect);
          } else if (currentTool == Ellipse) {
              QRect rect(lastPoint, currentPoint);
              painter.drawEllipse(rect);
          }
      }

}




void PaintWidgets::openFile() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Ouvrir un fichier"), QDir::homePath(), tr("Images (*.png *.jpeg *.jpg)"));
    if (!fileName.isEmpty()) {
        QImage image;
        if (image.load(fileName)) {
            canvas = QPixmap::fromImage(image);
            update();
            this->resize(canvas.size());

        } else {
            QMessageBox::warning(this, tr("Ouvrir un fichier"), tr("Le fichier n'a pas pu être ouvert."));
        }
    }
}

void PaintWidgets::saveImage() {
    if (!filePath.isEmpty()) {
        canvas.save(filePath);
    }
}

void PaintWidgets::on_actionSauvegarder_triggered()
{
    saveChange=true;
    saveImage();
}


void PaintWidgets::on_actionOuvrir_triggered()
{
    openFile();
}

QIcon PaintWidgets::createColorIcon(const QColor &color)
{
    QPixmap pixmap(200, 150);
    pixmap.fill(color);
    return QIcon(pixmap);

}

void PaintWidgets::onColorPickerClicked()

{
    QColor newColor = QColorDialog::getColor(currentColor, this, tr("Choisir une couleur"));
    if(newColor.isValid()){
        currentColor = newColor;
        colorPickerAction->setIcon(createColorIcon(currentColor));
    }

}

void PaintWidgets::updateCursorForDrawing() {
    int diameter = intensity * 2;
    QPixmap pixmap(diameter + 2, diameter + 2);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::black);
    painter.drawEllipse(1, 1, diameter, diameter);
    QCursor cursor(pixmap);
    setCursor(cursor);
}

void PaintWidgets::checkAndUncheck(QAction *newC){
    currentCheck->setChecked(false);
    currentCheck = newC;
    currentCheck->setChecked(true);

}


void PaintWidgets::setIntensity(int value)
{
    intensity = value;
    updateCursorForDrawing();

}

void PaintWidgets::floodFill(const QPoint &startPoint, const QColor &newColor, QPainter &painter) {
    if (!canvas.rect().contains(startPoint)) {
        return;
    }

    QImage image = canvas.toImage();
    QColor targetColor = image.pixelColor(startPoint);
    if (newColor == targetColor) {
        return;
    }

    QQueue<QPoint> queue;
    queue.enqueue(startPoint);

    painter.setPen(QPen(newColor, 1));

    while (!queue.isEmpty()) {
        QPoint p = queue.dequeue();
        if (!canvas.rect().contains(p)) continue;
        if (image.pixelColor(p) != targetColor) continue;
        painter.drawPoint(p);
        queue.enqueue(QPoint(p.x() + 1, p.y()));
        queue.enqueue(QPoint(p.x() - 1, p.y()));
        queue.enqueue(QPoint(p.x(), p.y() + 1));
        queue.enqueue(QPoint(p.x(), p.y() - 1));
        image.setPixelColor(p, newColor);
    }

    update();
}

void PaintWidgets::applyZoom(double zoomFactor, const QPoint zoomCenterPoint)
{
    QPointF zoomCenter = zoomCenterPoint - contentOffset;
    double newZoomLevel = zoomLevel * zoomFactor;
    double minZoomLevel = 1.0;

    if (newZoomLevel < minZoomLevel) {
        newZoomLevel = minZoomLevel;
        zoomFactor = newZoomLevel / zoomLevel;
    }

    double scaleChange = zoomFactor - 1.0;
    contentOffset -= QPointF(zoomCenter.x() * scaleChange, zoomCenter.y() * scaleChange);
    zoomLevel = newZoomLevel;

    update();
}



void PaintWidgets::on_pen_triggered()
{
    currentTool= Pen;
    checkAndUncheck(ui->pen);
    updateCursorForDrawing();
}


void PaintWidgets::on_eraser_triggered()
{
    currentTool = Eraser;
    checkAndUncheck(ui->eraser);
    updateCursorForDrawing();
}


void PaintWidgets::on_bucket_triggered()
{
    currentTool = Bucket;
    checkAndUncheck(ui->bucket);
    QPixmap bucketCursorPixmap(":/icon/Icons/bucket.png");
    bucketCursorPixmap = bucketCursorPixmap.scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    QCursor bucketCursor(bucketCursorPixmap);
    setCursor(bucketCursor);
}


void PaintWidgets::on_pipet_triggered()
{

    currentTool = Pipet;
    checkAndUncheck(ui->pipet);
    QPixmap bucketCursorPixmap(":/icon/Icons/pipet.png");
    bucketCursorPixmap = bucketCursorPixmap.scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    QCursor bucketCursor(bucketCursorPixmap);
    setCursor(bucketCursor);


}


void PaintWidgets::on_loupe_triggered()
{
    currentTool = Loupe;
    checkAndUncheck(ui->loupe);
    QPixmap bucketCursorPixmap(":/icon/Icons/loupe.png");
    bucketCursorPixmap = bucketCursorPixmap.scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    QCursor bucketCursor(bucketCursorPixmap);
    setCursor(bucketCursor);

}


void PaintWidgets::on_line_triggered()
{
    currentTool = Line;
    checkAndUncheck(ui->line);
    setCursor(Qt::CrossCursor);

}


void PaintWidgets::on_rectangle_triggered()
{
    currentTool = Rectangle;
    checkAndUncheck(ui->rectangle);
    setCursor(Qt::CrossCursor);

}


void PaintWidgets::on_circle_triggered()
{
    currentTool = Ellipse;
    checkAndUncheck(ui->circle);
    setCursor(Qt::CrossCursor);

}

void PaintWidgets::closeEvent(QCloseEvent *event) {
    if (saveChange==false) {
        QMessageBox::StandardButton reply = QMessageBox::question(this, tr("Confirmer la fermeture"),
                                                                  tr("Des modifications non sauvegardées ont été détectées. Voulez-vous sauvegarder vos changements avant de quitter ?"),
                                                                  QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
        if (reply == QMessageBox::Yes) {
            saveImage();
            event->accept();
        } else if (reply == QMessageBox::No) {
            event->accept();
        } else {
            event->ignore();
        }
    } else {
        event->accept();
    }
}

void PaintWidgets::on_undo_triggered()
{
    saveChange=false;
    undoStack.undo();

}


void PaintWidgets::on_redo_triggered()
{
    saveChange=false;
    undoStack.redo();
}


void PaintWidgets::on_actionQuitter_triggered()
{
    saveChange=true;
    saveImage();
    this->close();
}


void PaintWidgets::on_newPaper_triggered()
{
    saveChange=false;

    initialState = canvas;
    canvas.fill(Qt::white);
    finalState = canvas;

    undoStack.push(new DrawingCommand(initialState, finalState, [this](const QPixmap& state) {
        canvas = state;
        update();
    }));
}


void PaintWidgets::on_actionNouveau_triggered()
{
    Dialog dialog;
    dialog.setModal(true);
    close();
    dialog.exec();
}

