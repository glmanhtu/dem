#ifndef MOVEMODULE_H
#define MOVEMODULE_H

#include "Modules/moduleinterface.h"
#include "movegraphics.h"

class MoveModule : public ModuleInterface
{
private:
    MoveGraphics* graphics;
public:
    MoveModule();

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

#endif // MOVEMODULE_H
