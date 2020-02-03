#include "widget.h"

#include <QApplication>
#include <cserver.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CServer server(2323);
    server.show();
    return a.exec();
}
