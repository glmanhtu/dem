#include "rotatecontroller.h"

RotateController::RotateController(QObject *parent): QObject(parent)
{

}


void RotateController::initAction()
{
}

void RotateController::terminalAction()
{
}

QString RotateController::getActionName()
{
    return "Rotate.RotateController";
}

bool RotateController::loadOnBoot()
{
    return true;
}

bool RotateController::requireDemObject()
{
    return false;
}

void RotateController::setDemObject(DemInterface *)
{
}

DemInterface *RotateController::getDemObject()
{
    return NULL;
}

void RotateController::setGraphics(GraphicsComposite *)
{
}

void RotateController::setActionPerform(ActionListener *action)
{
    actionListener = action;
}
