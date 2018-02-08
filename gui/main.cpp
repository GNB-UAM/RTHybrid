#include "rthybrid.h"
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RTHybrid w;
    w.show();

    return a.exec();
}
