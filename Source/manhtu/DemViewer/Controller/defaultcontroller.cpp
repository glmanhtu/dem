#include "defaultcontroller.h"
#include "Model/demobject.h"

DefaultController::DefaultController()
{
    demObject = new DemObject();
}

void DefaultController::initGraphics()
{            
    window.setDemObject(demObject);
    window.setActionPerform(actionListener);
    window.setMainGraphics(&window);
    window.setSize(900, 600);
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
    modules->setGraphics(&window);
    modules->loadModules();
}

void DefaultController::start()
{
    window.initial();
    window.show();
}

DefaultController::~DefaultController()
{

}
