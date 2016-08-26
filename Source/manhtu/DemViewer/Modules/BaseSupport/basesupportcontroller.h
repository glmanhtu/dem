#ifndef BASESUPPORTCONTROLLER_H
#define BASESUPPORTCONTROLLER_H

#include <QObject>
#include "Controller/actioninterface.h"
#include "Model/deminterface.h"
#include "Controller/actionlistener.h"
#include "Modules/Color/colorcontroller.h"

class BaseSupportController : public QObject, public ActionInterface
{
    Q_OBJECT
private:
    DemInterface* demObject;
    ActionListener* actions;
    float baseHeight;
    QVector3D color1, color2;

public:
    BaseSupportController(QObject *parent = 0);

    // ActionInterface interface
public:
    void initAction();
    void terminalAction();
    QString getActionName();
    bool loadOnBoot();
    bool requireDemObject();
    void setDemObject(DemInterface *);
    DemInterface *getDemObject();
    void setGraphics(GraphicsComposite *);
    void generateBaseSupport();    
    void generateTriangleInSide(int x, int y, ColorController* colorController, Vertex* vertexs);
    // ActionInterface interface
public:
    void setActionPerform(ActionListener *);
};

#endif // BASESUPPORTCONTROLLER_H
