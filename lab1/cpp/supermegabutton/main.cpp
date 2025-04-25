#include "supermegabutton.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    SuperMegaButton w;
    w.show();
    return a.exec();
}
