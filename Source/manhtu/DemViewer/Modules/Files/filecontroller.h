#ifndef FILECONTROLLER_H
#define FILECONTROLLER_H
#include <QObject>
#include "Controller/actioninterface.h"

class FileController : public QObject, public ActionInterface
{
Q_OBJECT
public:
    FileController(QObject *parent = 0);
    void openFile();

    // ActionInterface interface
public:
    void initAction();
    void terminalAction();
    QString getActionName();
    bool loadOnBoot();
    bool requireDemObject();
    void setDemObject(DemInterface *);
};

#endif // FILECONTROLLER_H
