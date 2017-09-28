#ifndef DRAWIMAGE_H
#define DRAWIMAGE_H

#include <QMainWindow>
#include <QColor>

namespace Ui {
class DrawImage;
}

class DrawImage : public QMainWindow
{
    Q_OBJECT

public:
    explicit DrawImage(QWidget *parent = 0);
    ~DrawImage();

private slots:
    void brushColor();
    void drawColor();
    void changeWidth(int);
    void changeRem(bool val);
    void DrawNewImage(QString file);

private:
    Ui::DrawImage *ui;
    QColor _brushColor;
    QColor _drawColor;
};

#endif // DRAWIMAGE_H
