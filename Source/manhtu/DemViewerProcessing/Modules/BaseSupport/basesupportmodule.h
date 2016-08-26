#ifndef BASESUPPORTMODULE_H
#define BASESUPPORTMODULE_H

#include "Modules/moduleinterface.h"
#include "basesupportcontroller.h"

class BaseSupportModule : public ModuleInterface
{
private:
    BaseSupportController bsController;

public:
    BaseSupportModule();

    // ModuleInterface interface
public:
    bool hasGraphics();
    GraphicsComposite *getGraphic();
    bool hasAction();
    ActionInterface *getAction();
    bool loadOnBoot();
    QString getModuleName();
    void initModule();
    void terminalModule();
};

#endif // BASESUPPORTMODULE_H
