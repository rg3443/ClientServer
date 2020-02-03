#include "widget.h"

#include <QApplication>
#include "cclient.h"
#include "ckeyinput.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CClient clientWindow("localhost",2323);
    clientWindow.show();
    return a.exec();
}
