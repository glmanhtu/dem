#include "filemodule.h"

FilesModule::FilesModule()
{
    fgraphics = new FileGraphics(&fcontroller);
}

FilesModule::~FilesModule()
{
}

bool FilesModule::hasAction()
{
    return true;
}

bool FilesModule::hasGraphics()
{
    return true;
}

GraphicsComposite* FilesModule::getGraphic()
{
    return fgraphics;
}
ActionInterface * FilesModule::getAction()
{
    return &fcontroller;
}
bool FilesModule::loadOnBoot()
{
    return false;
}
QString FilesModule::getModuleName()
{
    return QString("Files");
}
void FilesModule::initModule()
{
    fgraphics->initial();
}

void FilesModule::terminalModule()
{

}

