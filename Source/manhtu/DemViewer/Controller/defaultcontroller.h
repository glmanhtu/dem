#ifndef DEFAULTCONTROLLER_H
#define DEFAULTCONTROLLER_H

#include "actionlistener.h"
#include "Model/deminterface.h"
#include "modulecontroller.h"
#include "View/graphics.h"

class DefaultController
{
private:
    ActionListener* actionListener;
    DemInterface* demObject;
    ModuleController* modules;
    Graphics graphics;
public:
    DefaultController();
    ~DefaultController();
    void initGraphics();
    void initActions();
    void initModules();
    void start();
};

#endif // DEFAULTCONTROLLER_H
