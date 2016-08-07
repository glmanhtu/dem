#ifndef FILECONTROLLER_H
#define FILECONTROLLER_H
#include <QObject>
#include "Controller/actioninterface.h"
#include "View/graphicscomposite.h"

class FileController : public QObject, public ActionInterface
{
Q_OBJECT
public:
    FileController(QObject *parent = 0);
    DemInterface* demObject;
    GraphicsComposite* graphics;
    void openFile();

    // ActionInterface interface
public:
    void initAction() override;
    void terminalAction() override;
    QString getActionName() override;
    bool loadOnBoot() override;
    bool requireDemObject() override;
    void setDemObject(DemInterface *) override;
    DemInterface* getDemObject() override;
    void setGraphics(GraphicsComposite*) override;
};

#endif // FILECONTROLLER_H
