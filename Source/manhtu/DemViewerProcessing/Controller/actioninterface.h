#ifndef ACTIONINTERFACE_H
#define ACTIONINTERFACE_H
#include "Model/deminterface.h"
#include <iostream>
#include <QWidget>

class GraphicsComposite;

using namespace std;
class ActionInterface
{
public:
    virtual void initAction() = 0;
    virtual void terminalAction() = 0;
    virtual QString getActionName() = 0;
    virtual bool loadOnBoot() = 0;
    virtual bool requireDemObject() = 0;
    virtual void setDemObject(DemInterface*) = 0;
    virtual DemInterface* getDemObject()=0;
    virtual void setGraphics(GraphicsComposite*)=0;
};

#endif // ACTIONINTERFACE_H
