#include "basesupportcontroller.h"
#include "View/vertex.h"
#include "Modules/Color/colorcontroller.h"

BaseSupportController::BaseSupportController(QObject *parent): QObject(parent)
{

}


void BaseSupportController::initAction()
{
}

void BaseSupportController::terminalAction()
{
}

QString BaseSupportController::getActionName()
{
    return "BaseSupport.BaseSupportController";
}

bool BaseSupportController::loadOnBoot()
{
    return true;
}

bool BaseSupportController::requireDemObject()
{
    return true;
}

void BaseSupportController::setDemObject(DemInterface * dem)
{
    demObject = dem;
}

DemInterface *BaseSupportController::getDemObject()
{
    return NULL;
}

void BaseSupportController::setGraphics(GraphicsComposite *)
{
}

void BaseSupportController::generateBaseSupport()
{
    float x1, y1, z1, x3, y3, z3, tempZ;
    QVector3D color1, color2;
    tempZ = -11000;
    ColorController* colorController = (ColorController*)actions->getAction(QString("Color.ColorController"));
    float* demData = demObject->getVertexArray();
    for (int i=0; i<demObject->getCols()*9 - 9; i=i+18) {
        x1 = demData[i];
        y1 = demData[i+1];
        z1 = demData[i+2];
        x3 = demData[i+12];
        y3 = demData[i+13];
        z3 = demData[i+14];
        demObject->addVertex(
            Vertex(
                QVector3D(x1,y1,z1),
                QVector3D(demData[i+3], demData[i+4], demData[i+5])
            )
        );
        demObject->addVertex(
            Vertex(
                QVector3D(x3,y3,z3),
                QVector3D(demData[i+15], demData[i+16], demData[i+17])
            )
        );
        if (z1 > z3) {
            color1 = QVector3D(demData[i+3], demData[i+4], demData[i+5]);
            demObject->addVertex(
                Vertex(
                    QVector3D(x1,y1,z3),
                    color1
                )
            );
            tempZ = z3;
        } else {
            color1 = QVector3D(demData[i+15], demData[i+16], demData[i+17]);
            demObject->addVertex(
                Vertex(
                    QVector3D(x3,y3,z1),
                    color1
                )
            );
            tempZ = z1;
        }

        float scaledMinHeight = demObject->heightScale(demObject->minHeight());
        if (tempZ > scaledMinHeight) {
            color2 = colorController->getVectorColor(demObject->minHeight());
            demObject->addVertex(
                Vertex(
                    QVector3D(x1,y1,tempZ),
                    color1
                )
            );
            demObject->addVertex(
                Vertex(
                    QVector3D(x3,y3,tempZ),
                    color1
                )
            );
            demObject->addVertex(
                Vertex(
                    QVector3D(x3,y3,scaledMinHeight),
                    color1
                )
            );
            demObject->addVertex(
                Vertex(
                    QVector3D(x1,y1,scaledMinHeight),
                    color1
                )
            );
            demObject->addVertex(
                Vertex(
                    QVector3D(x3,y3,scaledMinHeight),
                    color1
                )
            );
            demObject->addVertex(
                Vertex(
                    QVector3D(x1,y1,tempZ),
                    color1
                )
            );
        }

    }
}


void BaseSupportController::setActionPerform(ActionListener *actions)
{
    this->actions = actions;
}
