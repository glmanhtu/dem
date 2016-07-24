#include "demproject.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    DemProject w;
    w.show();

    return app.exec();
}
