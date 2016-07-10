#ifndef MODULECONTROLLER_H
#define MODULECONTROLLER_H

#include "actionlistener.h"
#include "View/graphics.h"
#include "actioninterface.h"
#include "View/graphicscomposite.h"
#include "Model/deminterface.h"
#include "Modules/moduleinterface.h"

class ModuleController
{
private:
    ActionListener* actions;
    Graphics* graphics;
    vector<ModuleInterface*> modules;
public:
    ModuleController();
    void loadModules();
    void registerAction(ActionInterface*);
    void registerGraphics(GraphicsComposite*);
    void registerDemObject(DemInterface*);
    void setActionListener(ActionListener*);
    void setGraphics(Graphics*);
};

#endif // MODULECONTROLLER_H
