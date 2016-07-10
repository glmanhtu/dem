#include "defaultcontroller.h"

DefaultController::DefaultController()
{

}

void DefaultController::initGraphics()
{
    graphics.setActionPerform(*actionListener);
    graphics.setMainGraphics(&graphics);
}

void DefaultController::initActions()
{
    actionListener = new ActionListener();
}

void DefaultController::initModules()
{
    modules = new ModuleController();
    modules->setActionListener(actionListener);
    modules->setGraphics(&graphics);
    modules->loadModules();
}

void DefaultController::start()
{
    graphics.initial();
    graphics.show();
}

DefaultController::~DefaultController()
{

}
