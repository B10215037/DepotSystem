#include "userview.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UserView w;
    w.show();

    return a.exec();
}
