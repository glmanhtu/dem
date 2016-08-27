#ifndef ZOOMMODULE_H
#define ZOOMMODULE_H

#include "Modules/moduleinterface.h"
#include "zoomgraphics.h"

class ZoomModule: public ModuleInterface
{
private:
    ZoomGraphics* graphics;
public:
    ZoomModule();

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
