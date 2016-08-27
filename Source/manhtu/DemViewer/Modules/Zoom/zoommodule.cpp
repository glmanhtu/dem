#include "zoommodule.h"

ZoomModule::ZoomModule()
{
    graphics = new ZoomGraphics();
}


bool ZoomModule::hasGraphics()
{
    return true;
}

GraphicsComposite *ZoomModule::getGraphic()
{
    return graphics;
}

bool ZoomModule::hasAction()
{
    return false;
}

ActionInterface *ZoomModule::getAction()
{
    return NULL;
}

bool ZoomModule::loadOnBoot()
{
    return true;
}

QString ZoomModule::getModuleName()
{
    return QString("Zoom");
}

void ZoomModule::initModule()
{
}

void ZoomModule::terminalModule()
{
}
