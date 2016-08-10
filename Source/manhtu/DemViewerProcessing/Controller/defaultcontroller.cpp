#include "defaultcontroller.h"
#include "Model/demmodel.h"

DefaultController::DefaultController()
{
    demObject = new DemModel();
}

void DefaultController::initGraphics()
{
    graphics = mainWindow.getGraphics();
    graphics->setActionPerform(actionListener);
    graphics->setMainGraphics(graphics);
    graphics->setDemObject(demObject);
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
    mainWindow.show();
}

DefaultController::~DefaultController()
{

}
