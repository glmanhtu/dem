#ifndef MODULEINTERFACE_H
#define MODULEINTERFACE_H

#include "View/graphicscomposite.h"
#include "Controller/actioninterface.h"

class ModuleInterface
{
public:
    virtual bool hasGraphics() = 0;
    virtual GraphicsComposite* getGraphic() = 0;
    virtual bool hasAction() = 0;
    virtual ActionInterface* getAction() = 0;
    virtual bool loadOnBoot() = 0;
    virtual QString getModuleName() = 0;
    virtual void initModule() = 0;
    virtual void terminalModule() = 0;
};

#endif // MODULEINTERFACE_H
