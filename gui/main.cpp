#include "rtbiomanager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RTBiomanager w;
    w.show();

    return a.exec();
}
