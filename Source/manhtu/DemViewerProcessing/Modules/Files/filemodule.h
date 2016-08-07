#ifndef FILEMODULE_H
#define FILEMODULE_H

#include "Modules/moduleinterface.h"
#include "filegraphics.h"
#include "filecontroller.h"

class FilesModule : public ModuleInterface
{
private:
    FileController fcontroller;
    FileGraphics* fgraphics;
public:
    FilesModule();
    ~FilesModule();
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

#endif // FILEMODULE_H
