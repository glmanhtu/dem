#include "movemodule.h"

MoveModule::MoveModule()
{
    graphics = new MoveGraphics();
}


bool MoveModule::hasGraphics()
{
    return true;
}

GraphicsComposite *MoveModule::getGraphic()
{
    return graphics;
}

bool MoveModule::hasAction()
{
    return false;
}

ActionInterface *MoveModule::getAction()
{
    return NULL;
}

bool MoveModule::loadOnBoot()
{
    return true;
}

QString MoveModule::getModuleName()
{
    return "Move";
}

void MoveModule::initModule()
{
}

void MoveModule::terminalModule()
{
}
