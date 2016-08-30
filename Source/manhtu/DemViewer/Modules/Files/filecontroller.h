#ifndef FILECONTROLLER_H
#define FILECONTROLLER_H
#include <QObject>
#include "Controller/actioninterface.h"
#include "View/graphicscomposite.h"
#include "Controller/actionlistener.h"
#include "Modules/Color/colorcontroller.h"

class FileController : public QObject, public ActionInterface
{
Q_OBJECT
private:
    DemInterface* demObject;
    GraphicsComposite* graphics;
    ActionListener* actions;
    ColorController* colorController;
    bool hasFile;
    float maxZ;
    float scale;
    void readFile();
    float getZCoordinate(float height);

public:
    FileController(QObject *parent = 0);
    void initAction() override;
    void terminalAction() override;
    QString getActionName() override;
    bool loadOnBoot() override;
    bool requireDemObject() override;
    void setDemObject(DemInterface *) override;
    DemInterface* getDemObject() override;
    void setGraphics(GraphicsComposite*) override;
    bool isOpenedFile();
    void openFile();    

    // ActionInterface interface
public:
    void setActionPerform(ActionListener *) override;
};

#endif // FILECONTROLLER_H
