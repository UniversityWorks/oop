#include "dynamicbuttons.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DynamicButtons w;
    w.show();
    return a.exec();
}
