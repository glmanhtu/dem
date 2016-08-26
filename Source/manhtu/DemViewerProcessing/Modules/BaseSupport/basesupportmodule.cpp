#include "basesupportmodule.h"

BaseSupportModule::BaseSupportModule()
{

}


bool BaseSupportModule::hasGraphics()
{
    return false;
}

GraphicsComposite *BaseSupportModule::getGraphic()
{
    return NULL;
}

bool BaseSupportModule::hasAction()
{
    return true;
}

ActionInterface *BaseSupportModule::getAction()
{
    return &bsController;
}

bool BaseSupportModule::loadOnBoot()
{
    return true;
}

QString BaseSupportModule::getModuleName()
{
    return "BaseSupport";
}

void BaseSupportModule::initModule()
{
}

void BaseSupportModule::terminalModule()
{
}
