#ifndef ROTATEMODULE_H
#define ROTATEMODULE_H

#include "Modules/moduleinterface.h"
#include "rotatecontroller.h"
#include "rotategraphics.h"

class RotateModule : public ModuleInterface
{
private:
    RotateController rotateController;
    RotateGraphics* graphics;
public:
    RotateModule();

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

#endif // ROTATEMODULE_H
