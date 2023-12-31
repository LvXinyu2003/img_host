#include "home_page.h"

#include <QApplication>

#include <QPalette>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    home_page w;

    QPalette palette(w.palette());
    palette.setColor(QPalette::Window, QColor("white"));
    w.setAutoFillBackground(true);
    w.setPalette(palette);

    w.show();
    return a.exec();
}
