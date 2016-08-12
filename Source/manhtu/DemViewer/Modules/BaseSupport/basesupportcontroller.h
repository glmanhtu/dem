#ifndef BASESUPPORTCONTROLLER_H
#define BASESUPPORTCONTROLLER_H

#include <QObject>
#include "Controller/actioninterface.h"
#include "Model/deminterface.h"
#include "Controller/actionlistener.h"

class BaseSupportController : public QObject, public ActionInterface
{
    Q_OBJECT
private:
    DemInterface* demObject;
    ActionListener* actions;

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

    // ActionInterface interface
public:
    void setActionPerform(ActionListener *);
};

#endif // BASESUPPORTCONTROLLER_H
