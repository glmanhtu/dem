#include "rotatemodule.h"

RotateModule::RotateModule()
{
    graphics = new RotateGraphics();
}


bool RotateModule::hasGraphics()
{
    return true;
}

GraphicsComposite *RotateModule::getGraphic()
{
    return graphics;
}

bool RotateModule::hasAction()
{
    return true;
}

ActionInterface *RotateModule::getAction()
{
    return &rotateController;
}

bool RotateModule::loadOnBoot()
{
    return true;
}

QString RotateModule::getModuleName()
{
    return QString("Rotate");
}

void RotateModule::initModule()
{
}

void RotateModule::terminalModule()
{
}
