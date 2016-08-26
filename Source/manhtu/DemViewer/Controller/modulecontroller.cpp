#include "modulecontroller.h"
#include "Modules/Files/filemodule.h"
#include "Modules/Color/colormodule.h"
#include "Modules/BaseSupport/basesupportmodule.h"
#include "Modules/Rotate/rotatemodule.h"

ModuleController::ModuleController()
{
    modules.push_back(new RotateModule());
    modules.push_back(new ColorModule());
    modules.push_back(new BaseSupportModule());
    modules.push_back(new FilesModule());
}

void ModuleController::loadModules()
{
    for (int i=0; i<modules.size(); i++) {
        if (modules[i]->hasAction()) {
            modules[i]->getAction()->setActionPerform(actions);
            registerAction(modules[i]->getAction());
            modules[i]->getAction()->setGraphics(modules[i]->getGraphic());
        }
        if (modules[i]->hasGraphics()) {
            modules[i]->getGraphic()->setActionPerform(actions);
            registerGraphics(modules[i]->getGraphic());
        }
        modules[i]->initModule();
    }
}

void ModuleController::registerAction(ActionInterface* action)
{
    actions->registerAction(action);
}

void ModuleController::registerDemObject(DemInterface *)
{

}

void ModuleController::registerGraphics(GraphicsComposite * graphicsComposite)
{
    graphics->registerGraphics(graphicsComposite);
}

void ModuleController::setActionListener(ActionListener * action)
{
    actions = action;
}

void ModuleController::setGraphics(Graphics * g)
{
    graphics = g;
}
