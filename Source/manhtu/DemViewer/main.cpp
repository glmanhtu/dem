//#include "widget.h"
#include "View/graphics.h"
#include "Controller/defaultcontroller.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    QSurfaceFormat format;
//    format.setRenderableType(QSurfaceFormat::OpenGL);
//    format.setProfile(QSurfaceFormat::CoreProfile);
//    format.setVersion(3, 3);
//    QSurfaceFormat::setDefaultFormat(format);
    DefaultController* controller = new DefaultController();
    controller->initActions();
    controller->initGraphics();
    controller->initModules();
    controller->start();

    return a.exec();
}
