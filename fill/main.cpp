#include "drawimage.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DrawImage w;
    w.show();

    return a.exec();
}
