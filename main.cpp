#include "Calcule.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Calcule w;
    w.show();
    return QCoreApplication::exec();
}
