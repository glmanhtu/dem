//#include "widget.h"
#include "View/graphics.h"
#include "Controller/defaultcontroller.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DefaultController* controller = new DefaultController();
    controller->initActions();
    controller->initGraphics();
    controller->initModules();
    controller->start();

    return a.exec();
}
