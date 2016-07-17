#include "defaultcontroller.h"

DefaultController::DefaultController()
{
    demObject = NULL;
}

void DefaultController::initGraphics()
{
    graphics = graphicsGlobal.getGraphicsWidget();
    graphics->setActionPerform(actionListener);
    graphics->setMainGraphics(graphics);
}

void DefaultController::initActions()
{
    actionListener = new ActionListener();
    actionListener->setDemObject(demObject);
}

void DefaultController::initModules()
{
    modules = new ModuleController();
    modules->setActionListener(actionListener);
    modules->setGraphics(graphics);
    modules->loadModules();
}

void DefaultController::start()
{
    graphics->initial();
    graphicsGlobal.show();
}

DefaultController::~DefaultController()
{

}
