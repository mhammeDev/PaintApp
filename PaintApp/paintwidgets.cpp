#include "paintwidgets.h"
#include "ui_paintwidgets.h"



PaintWidgets::PaintWidgets(int width, int height, const QString &filePath, const QImage& image,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PaintWidgets),
    filePath(filePath),
    drawing(false)

{

    ui->setupUi(this);
    setWindowTitle(tr("Paint"));
    canvas = QPixmap(width, height);

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
        drawing = true;
        lastPoint = event->pos();
    }
}



void PaintWidgets::mouseMoveEvent(QMouseEvent *event) {

    if ((event->buttons() & Qt::LeftButton) && drawing) {

        QPainter painter(&canvas);

        painter.setPen(QPen(Qt::black, 3));

        painter.drawLine(lastPoint, event->pos());
        lastPoint = event->pos();
        update();
    }

}



void PaintWidgets::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && drawing) {
        drawing = false;
    }
}

void PaintWidgets::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, canvas);
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
    saveImage();
}


void PaintWidgets::on_actionOuvrir_triggered()
{
    openFile();
}

