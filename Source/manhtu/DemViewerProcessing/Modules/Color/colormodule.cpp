#include "colormodule.h"

ColorModule::ColorModule()
{

}


bool ColorModule::hasGraphics()
{
    return false;
}

GraphicsComposite *ColorModule::getGraphic()
{
    return NULL;
}

bool ColorModule::hasAction()
{
    return true;
}

ActionInterface *ColorModule::getAction()
{
    return &colorController;
}

bool ColorModule::loadOnBoot()
{
    return true;
}

QString ColorModule::getModuleName()
{
    return "Color";
}

void ColorModule::initModule()
{
}

void ColorModule::terminalModule()
{
}
