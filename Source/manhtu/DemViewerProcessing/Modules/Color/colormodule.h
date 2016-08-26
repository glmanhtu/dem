#ifndef COLORMODULE_H
#define COLORMODULE_H

#include "Modules/moduleinterface.h"
#include "colorcontroller.h"

class ColorModule : public ModuleInterface
{

private:
    ColorController colorController;
public:
    ColorModule();

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

#endif // COLORMODULE_H
