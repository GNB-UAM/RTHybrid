#include "rthybrid.h"
#include "rthybrid_xml_main.h"
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    if ((argc >= 3) && (strcmp("-xml", argv[1]) == 0)) {
        rthybrid_xml_main xml;
        return xml.xml_init(argv[2]);
    }

    QApplication a(argc, argv);
    RTHybrid w;
    w.show();

    return a.exec();
}
