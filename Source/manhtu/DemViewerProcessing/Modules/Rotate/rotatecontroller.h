#ifndef ROTATECONTROLLER_H
#define ROTATECONTROLLER_H

#include <QObject>
#include "Controller/actioninterface.h"
#include "Controller/actionlistener.h"

class RotateController : public QObject, public ActionInterface
{
    Q_OBJECT
private:
    ActionListener* actionListener;
public:
    RotateController(QObject *parent = 0);

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
    void setActionPerform(ActionListener *);
};

#endif // ROTATECONTROLLER_H
