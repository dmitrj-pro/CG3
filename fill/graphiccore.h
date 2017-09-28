#ifndef GROPHICCORE_H
#define GROPHICCORE_H
#include <QGraphicsView>
#include <QFileDialog>
#include <QColorDialog>
#include <QObject>
#include <QGraphicsItemGroup>
#include <QPen>
#include <QBrush>
#include <QMouseEvent>


inline void getUsetColor(QColor & res){
    QColorDialog * dialog = new QColorDialog();
    QColor tmp = dialog->getColor();
    delete dialog;
    if (!tmp.isValid())
        return;
    res = tmp;
}

bool showImage(QGraphicsView * view, QString filename);

inline bool getUserFile(QString & res){
    QFileDialog * d =new QFileDialog();
    res = d->getOpenFileName(0, "Open Dialog", "", "*.jpg *.jpeg *.png");
    delete d;
}

class Line;

class Canvas : public QGraphicsView {
    Q_OBJECT
    private:
        QColor _c;
        QColor _c_draw;
        int _w;
        bool _lock;
        QString file_name;
    public:
        explicit Canvas(int h, int w, QWidget *parent = 0);
        explicit Canvas(QWidget *parent = 0);
        inline void setColor(QColor c){
            _c = c;
        }
        inline void setWidth(size_t w){
            _w =w;
        }

        inline void Lock(){
            _lock = true;
        }
        inline void Unlock(){
            _lock = false;
        }
        inline void Lock(bool v){
            _lock = v;
        }
        inline bool isLock(){
            return _lock;
        }
        inline void setDrawColor(QColor c){
            _c_draw = c;
            file_name="";
        }
        inline void setDrawFile(QString c){
            file_name=c;
        }

        void Save (QString name);
    signals:
        void Success(QString file);
    public slots:
        void resizeEvent(QResizeEvent *);
    protected slots:
        void mousePressEvent(QMouseEvent *event);
        void mouseMoveEvent(QMouseEvent *event);
        void mouseReleaseEvent(QMouseEvent *event);
    protected:
        QGraphicsScene m_scene;
        Line *m_line;
        bool m_isKeyPressed;
};

#endif // GROPHICCORE_H
