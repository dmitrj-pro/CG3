#include "graphiccore.h"
#include <vector>
#include <cmath>

#include <iostream>

using std::vector;

vector<vector<QColor>> readImage(QString in_filename){
    QImage * img = new QImage(in_filename);

    vector<vector<QColor>> res;
    for (int w = 0; w < img->width(); w++){
        res.push_back(vector<QColor>());
        for (int h = 0; h <img->height(); h++)
            res[w].push_back(QColor(img->pixel(w,h)));
    }
    return res;
}

void SaveImage(const vector<vector<QColor>>& img, QString filename){
    QImage * res = new QImage(QSize(img.size(),img[0].size()),QImage::Format_RGB32 );
    for (int w = 0; w<img.size(); w++)
        for (int h = 0; h<img[w].size(); h++)
            res->setPixel(w,h , img[w][h].rgb());
    res->save(filename);
}

void DrawLine(vector<vector<QColor>>& img, int x1, int y1, int x2, int y2, QColor c){
    for (int x = x1; x<= x2; x++)
        for (int y=y1; y<=y2; y++)
            img[x][y]=c;
}

void toLeft(vector<vector<QColor>>& img, int x, int y, QColor c, int& xr){
    for (int i = x; i <img.size(); i++){
        if (img[i][y] != c){
            xr = i;
            return;
        }
    }
    xr = img.size()-1;
}
void toRight(vector<vector<QColor>>& img, int x, int y, QColor c, int& xr){
    for (int i = x; i >= 0; i--){
        if (img[i][y] != c){
            xr = i;
            return;
        }
    }
    xr = 0;
}
void toUp(vector<vector<QColor>>& img, int x, int y, QColor c, int& yr){
    for (int i = y; i <img[x].size(); i++){
        if (img[x][i] != c){
            yr = i;
            return;
        }
    }
    yr = img[x].size()-1;
}
void toDown(vector<vector<QColor>>& img, int x, int y, QColor c, int& yr){
    for (int i = y; i >= 0; i--){
        if (img[x][i] != c){
            yr = i;
            return;
        }
    }
    yr = 0;
}

struct Point{
    int x;
    int y;
    Point(int x, int y):x(x), y(y){}
    Point():x(0), y(0){}
};

inline bool Equal(QColor c1, QColor c2){
    int Epsilon = 15;
    if (abs(c1.green() - c2.green()) > Epsilon)
        return false;
    if (abs(c1.red() - c2.red()) > Epsilon)
        return false;
    if (abs(c1.blue() - c2.blue()) > Epsilon)
        return false;
    return true;
}

void Draw(vector<vector<QColor>>& img, int w, int h, QColor oldColor, QColor newColor){
    int pos=0;
    vector<Point> sizes;

    Point point(w,h);
    sizes.push_back(point);

    while (pos < sizes.size()){
        point = sizes[pos++];
        int y1 = point.y;

        if (Equal (img[point.x][y1], newColor))
            continue;

        while (y1 >= 0 && Equal(img[point.x][y1], oldColor)) { y1 = y1 - 1; }
        y1 = y1 + 1;
        int spanLeft = 0;
        int spanRight = 0;
        while (y1 < img[point.x].size() && Equal(img[point.x][y1], oldColor)) {
            img[point.x][y1] = newColor;

            if (spanLeft == 0 && point.x > 0 && Equal(img[point.x-1][y1], oldColor)) {
                sizes.push_back(Point(point.x-1, y1));
                spanLeft = 1;
            }
            if (spanLeft == 1 && point.x > 0 && ! Equal(img[point.x-1][y1], oldColor)) {
                spanLeft = 0;
            }


            if (spanRight == 0 && point.x < (img.size()-1) && Equal(img[point.x+1][y1], oldColor)) {
                sizes.push_back(Point(point.x+1, y1));
                spanRight= 1;
            }            if (spanRight == 1 && point.x < (img.size()-1) && !Equal(img[point.x+1][y1], oldColor)) {
                spanRight = 0;
            }
            y1 = y1 + 1;
        }
    }

    point.x = w;
    point.y=h;
    sizes.push_back(point);
    pos=0;

    while (pos < sizes.size()){
        point = sizes[pos++];
        int y1 = point.x;

        if (Equal(img[y1][point.y], newColor))
            continue;

        while (y1 >= 0 && Equal(img[y1][point.y], oldColor)) { y1 = y1 - 1; }
        y1 = y1 + 1;
        int spanLeft = 0;
        int spanRight = 0;
        while (y1 < img.size() && Equal(img[y1][point.y], oldColor)) {
            img[y1][point.y] = newColor;

            if (spanLeft == 0 && point.y > 0 && Equal(img[y1][point.y-1], oldColor)) {
                sizes.push_back(Point(y1, point.y-1));
                spanLeft = 1;
            }
            if (spanLeft == 1 && point.y > 0 && !Equal(img[y1][point.y-1], oldColor)) {
                spanLeft = 0;
            }


            if (spanRight == 0 && point.y < (img[point.x].size()-1) && Equal(img[y1][point.y+1], oldColor)) {
                sizes.push_back(Point(y1, point.y+1));
                spanRight= 1;
            }
            if (spanRight == 1 && point.y < (img[point.x].size()-1) && !Equal(img[y1][point.y+1], oldColor)) {
                spanRight = 0;
            }
            y1 = y1 + 1;
        }
    }
}

void Draw(vector<vector<QColor>>& img, vector<vector<QColor>>& img2,  int w, int h, QColor oldColor){
    int pos=0;
    vector<Point> sizes;

    Point point(w,h);
    sizes.push_back(point);


    int img2W = img2.size() - 1;
    int img2H = img2[0].size() -1 ;
    size_t oldPos=0;

    while (pos == 0 || oldPos < sizes.size()) {
        pos = oldPos;
        while (pos < sizes.size()){
            point = sizes[pos++];
            int y1 = point.y;

            if (img[point.x][y1] == img2[point.x % img2W + 1] [ y1 % img2H +1 ])
            //if (Equal (img[point.x][y1], QColor(0,0,0)))
                continue;

            while (y1 >= 0 && Equal(img[point.x][y1], oldColor)) { y1 = y1 - 1; }
            y1 = y1 + 1;
            int spanLeft = 0;
            int spanRight = 0;
            while (y1 < img[point.x].size() && Equal(img[point.x][y1], oldColor)) {
                img[point.x][y1] = img2[point.x % img2W +1 ][ y1 % img2H +1 ];
                //img[point.x][y1] = QColor(0,0,0);

                if (spanLeft == 0 && point.x > 0 && Equal(img[point.x-1][y1], oldColor)) {
                    sizes.push_back(Point(point.x-1, y1));
                    spanLeft = 1;
                }
                if (spanLeft == 1 && point.x > 0 && ! Equal(img[point.x-1][y1], oldColor)) {
                    spanLeft = 0;
                }


                if (spanRight == 0 && point.x < (img.size()-1) && Equal(img[point.x+1][y1], oldColor)) {
                    sizes.push_back(Point(point.x+1, y1));
                    spanRight= 1;
                }
                if (spanRight == 1 && point.x < (img.size()-1) && !Equal(img[point.x+1][y1], oldColor)) {
                    spanRight = 0;
                }
                y1 = y1 + 1;
            }
        }

        point.x = w;
        point.y=h;
        sizes.push_back(point);
        int tmpPos = oldPos;
        oldPos = pos+1;
        pos=tmpPos;

        while (pos < sizes.size()){
            point = sizes[pos++];
            int y1 = point.x;

            if (Equal(img[y1][point.y], img2[y1 %img2W][ point.y % img2H]))
                continue;


            while (y1 >= 0 && Equal(img[y1][point.y], oldColor)) { y1 = y1 - 1; }
            y1 = y1 + 1;
            int spanLeft = 0;
            int spanRight = 0;
            while (y1 < img.size() && Equal(img[y1][point.y], oldColor)) {
                img[y1][point.y] = img2[y1 % img2W][ point.y % img2H];

                if (spanLeft == 0 && point.y > 0 && Equal(img[y1][point.y-1], oldColor)) {
                    sizes.push_back(Point(y1, point.y-1));
                    spanLeft = 1;
                }
                if (spanLeft == 1 && point.y > 0 && !Equal(img[y1][point.y-1], oldColor)) {
                    spanLeft = 0;
                }


                if (spanRight == 0 && point.y < (img[point.x].size()-1) && Equal(img[y1][point.y+1], oldColor)) {
                    sizes.push_back(Point(y1, point.y+1));
                    spanRight= 1;
                }
                if (spanRight == 1 && point.y < (img[point.x].size()-1) && !Equal(img[y1][point.y+1], oldColor)) {
                    spanRight = 0;
                }
                y1 = y1 + 1;
            }
        }
    }
}

void FullDraw(QString in_file, QString o_file, int x, int y, QColor oc, QColor nc){
    auto img = readImage(in_file);
    Draw(img,x % img.size(),y % img[0].size(),oc,nc);
    SaveImage(img, o_file);
}

void FullDraw2(QString in_file, QString z_file,  QString o_file, int x, int y, QColor oc, QColor nc){
    auto img = readImage(in_file);
    auto img2 = readImage(z_file);
    Draw(img,img2, x,y,oc);
    SaveImage(img, o_file);
}

class Line : public QGraphicsItemGroup, public QObject {
    const int EllipseRadius = 3;
    const int LineWidth = 1;
    QPen m_pen;
    QBrush m_brush;

    public:
        Line(const QColor &color, QObject *parent = 0): QGraphicsItemGroup(), QObject(parent),
                        m_pen(color), m_brush(color), m_lastPoint(nullptr){
            m_pen.setWidth(LineWidth);
        }

        inline void removePoint(){
            if (m_lastPoint)
                delete m_lastPoint;
            m_lastPoint = nullptr;
        }
        inline void setColor(QColor c){
            m_pen.setColor(c);
            m_brush.setColor(c);
        }
        inline void setWidth(size_t w){
            m_pen.setWidth(w);
        }

    public slots:
        void addPoint(QPointF point);

    protected:
        QGraphicsEllipseItem *m_lastPoint;
};

void Line::addPoint(QPointF point){
    QPointF radius(EllipseRadius, EllipseRadius);
    if (m_lastPoint) {
        QGraphicsLineItem *line = new QGraphicsLineItem(
        QLineF(m_lastPoint->pos(), point), this);
        line->setPen(m_pen);
        delete m_lastPoint;
    }
    m_lastPoint = new QGraphicsEllipseItem(QRectF(-radius, radius), this);
    m_lastPoint->setBrush(m_brush);
    m_lastPoint->setPos(point);
}

Canvas::Canvas(int h, int w, QWidget *parent): _lock(false), QGraphicsView(parent), m_scene(0, 0, w, h, this),m_isKeyPressed(false) {
    setScene(&m_scene);
    m_scene.setBackgroundBrush(QBrush(QColor(255,255,255)));
    fitInView(m_scene.sceneRect(), Qt::KeepAspectRatio);
}

Canvas::Canvas(QWidget *parent): _lock(false), QGraphicsView(parent), m_scene(0, 0, 670, 1000, this),m_isKeyPressed(false) {
    setScene(&m_scene);
    m_scene.setBackgroundBrush(QBrush(QColor(255,255,255)));
    fitInView(m_scene.sceneRect(), Qt::KeepAspectRatio);
}

void Canvas::mousePressEvent(QMouseEvent *event) {
    if (!_lock && event->button() == Qt::LeftButton) {
        QPointF pos = mapToScene(event->pos());
        m_line = new Line(_c, &m_scene);
        m_line->setWidth(_w);
        m_scene.addItem(m_line);
        m_line->addPoint(pos);
        m_isKeyPressed = true;
    }
    if (_lock && event->button() == Qt::LeftButton){
        //Save("tmp.jpg");
        QImage newImage(size(),QImage::Format_RGB32);
        QPainter painter(&newImage);

        m_scene.render(&painter);
        newImage.save("tmp.jpg");

        QColor tmpC=newImage.pixel(event->pos().rx(), event->pos().ry());
        if (file_name == "")
            FullDraw("tmp.jpg", "tmp.out.jpg", event->pos().rx(), event->pos().ry(), tmpC, _c_draw);
        else
            FullDraw2("tmp.jpg",file_name, "tmp.out.jpg", event->pos().rx(), event->pos().ry(), tmpC, _c_draw);
        emit Success("tmp.out.jpg");
    }
}

void Canvas::mouseMoveEvent(QMouseEvent *event) {
    if (!_lock && m_isKeyPressed) {
        QPointF pos = mapToScene(event->pos());
        m_line->addPoint(pos);
    }
}

void Canvas::Save(QString fileName){
    QImage newImage(size(),QImage::Format_RGB32);
    QPainter painter(&newImage);

    m_scene.render(&painter);
    newImage.save(fileName);

}

void Canvas::mouseReleaseEvent(QMouseEvent *event) {
    if (!_lock && event->button() == Qt::LeftButton) {
        m_isKeyPressed = false;
        m_line->removePoint();
    }
}

void Canvas::resizeEvent(QResizeEvent *) {
    m_scene.setBackgroundBrush(QBrush(QColor(255,255,255)));
    fitInView(m_scene.sceneRect(), Qt::KeepAspectRatio);
}


bool showImage(QGraphicsView * view, QString filename){
    if (filename == "")
        return false;
    QGraphicsScene* scene = new QGraphicsScene(NULL);
    view->setScene(scene);
    QGraphicsPixmapItem* pixmap_item = new QGraphicsPixmapItem();
    scene->addItem(pixmap_item);

    /** метод загружающий файл */
    QPixmap pixmap(filename);
    pixmap_item->setVisible(true);
    pixmap_item->setPixmap(pixmap);
    scene->setSceneRect(0, 0, pixmap.width(), pixmap.height());
    view->fitInView(pixmap_item, Qt::KeepAspectRatio);
    return true;
}
