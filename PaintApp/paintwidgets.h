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
#include <QSlider>
#include <QColorDialog>
#include <QQueue>
#include <QScrollArea>
#include <QGridLayout>
#include <QCloseEvent>
#include <QMessageBox>
#include <QUndoStack>



namespace Ui {

class PaintWidgets;
}

class PaintWidgets : public QMainWindow
{
    Q_OBJECT
    enum Tool { Pen, Eraser, Bucket, Pipet,Line ,Loupe, Rectangle, Ellipse, ColorPicker };

public:
    explicit PaintWidgets(int width = 500, int height = 500, const QString &filePath = QString(), const QImage& image = QImage(), QWidget *parent = nullptr);
    ~PaintWidgets();

public slots :
    void saveImage();
    void openFile();
    void checkAndUncheck(QAction *newC);
    void updateCursorForDrawing();
    void setIntensity(int value);
    void floodFill(const QPoint &startPoint, const QColor &newColor, QPainter &painter);
    void applyZoom(double zoomFactor, QPoint zoomCenter);


  protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    QIcon createColorIcon(const QColor &color);
    void closeEvent(QCloseEvent *event) override;


private slots:
    void on_actionSauvegarder_triggered();
    void on_actionOuvrir_triggered();
    void on_pen_triggered();
    void onColorPickerClicked();

    void on_eraser_triggered();

    void on_bucket_triggered();

    void on_pipet_triggered();

    void on_loupe_triggered();

    void on_line_triggered();

    void on_rectangle_triggered();

    void on_circle_triggered();

    void on_undo_triggered();

    void on_redo_triggered();

    void on_actionQuitter_triggered();

    void on_newPaper_triggered();

    void on_actionNouveau_triggered();

private:
    Ui::PaintWidgets *ui;
    QString filePath;
    bool drawing;
    QPixmap canvas;
    QPixmap tempLayer;
    QPoint lastPoint;
    Tool currentTool;
    QColor currentColor;
    int intensity;
    QAction * colorPickerAction =nullptr;
    QAction * currentCheck = nullptr;
    QSlider * intensitySlider = nullptr;
    double zoomLevel = 1.0;
    QPointF contentOffset = QPointF(0, 0);
    QPoint currentPoint;
    bool saveChange;
    QUndoStack undoStack;
    QPixmap initialState;
    QPixmap finalState;


};



#endif // PAINTWIDGETS_H
