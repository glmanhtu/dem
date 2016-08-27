#include "basesupportcontroller.h"
#include "View/vertex.h"

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
    baseHeight = demObject->heightScale(demObject->minHeight() - 1000);
    QVector3D normal;
    int step = demObject->getZoom();
    Vertex v1,v2,v3;
    ColorController* colorController = (ColorController*)actions->getAction(QString("Color.ColorController"));
    QVector3D baseHeightColor = colorController->getVectorColor(baseHeight);
    Vertex* demData = demObject->getArrayVertexs();
    for (int i=0; i<= demObject->getCols()-1-step; i=i+step) {

        // Top
        v1 = demData[demObject->getVertexPosition(i,0)];
        v2 = demData[demObject->getVertexPosition(i+step,0)];

        v3 = Vertex(
                        QVector3D(v1.position().x(), v1.position().y(),
                                  baseHeight),
                        baseHeightColor
                    );
        normal = QVector3D::normal(v1.position(), v2.position(), v3.position());
        v1.setNormal(normal);
        v2.setNormal(normal);
        v3.setNormal(normal);
        demObject->addVertex(v1, demObject->getVertexPosition(i,0));
        demObject->addVertex(v2, demObject->getVertexPosition(i+step,0));
        demObject->addVertex(v3, demObject->getVertexPosition(i,0,1,demObject->DIRECTION_NORTH));

        Vertex v4 = Vertex(
                        QVector3D(v2.position().x(), v2.position().y(), baseHeight),
                        baseHeightColor
                    );
        normal = QVector3D::normal(v2.position(), v3.position(), v4.position());
        v2.setNormal(normal);
        v3.setNormal(normal);
        v4.setNormal(normal);
        demObject->addVertex(v2, demObject->getVertexPosition(i+step, 0));
        demObject->addVertex(v3, demObject->getVertexPosition(i,0, 1, demObject->DIRECTION_NORTH));
        demObject->addVertex(v4, demObject->getVertexPosition(i+step,0, 1, demObject->DIRECTION_NORTH));
    }

    for (int i=0; i< demObject->getCols() - 1 -step; i= i+ step) {
        // Bottom
        v1 = demData[demObject->getVertexPosition(i,demObject->getRows()-1 - step)];
        v2 = demData[demObject->getVertexPosition(i+step,demObject->getRows()-1 - step)];

        v3 = Vertex(
                        QVector3D(v1.position().x(), v1.position().y(),
                                  baseHeight),
                        baseHeightColor
                    );
        normal = QVector3D::normal(v1.position(), v2.position(), v3.position());
        v1.setNormal(normal);
        v2.setNormal(normal);
        v3.setNormal(normal);
        demObject->addVertex(v1, demObject->getVertexPosition(i,demObject->getRows()-1 - step));
        demObject->addVertex(v2, demObject->getVertexPosition(i+step,demObject->getRows()-1 - step));
        demObject->addVertex(v3, demObject->getVertexPosition(i,demObject->getRows()-1 - step,1, demObject->DIRECTION_SOUTH));

        Vertex v4 = Vertex(
                        QVector3D(v2.position().x(), v2.position().y(), baseHeight),
                        baseHeightColor
                    );
        normal = QVector3D::normal(v2.position(), v3.position(), v4.position());
        v2.setNormal(normal);
        v3.setNormal(normal);
        v4.setNormal(normal);
        demObject->addVertex(v2, demObject->getVertexPosition(i+step, demObject->getRows()-1 - step));
        demObject->addVertex(v3, demObject->getVertexPosition(i,demObject->getRows()-1 - step, 1, demObject->DIRECTION_SOUTH));
        demObject->addVertex(v4, demObject->getVertexPosition(i+step,demObject->getRows()-1 - step, 1, demObject->DIRECTION_SOUTH));
    }

    for (int i=0; i<= demObject->getRows()-1 - step; i=i+step) {

        // Left
        v1 = demData[demObject->getVertexPosition(0, i)];
        v2 = demData[demObject->getVertexPosition(0,i + step)];

        v3 = Vertex(
                        QVector3D(v1.position().x(), v1.position().y(),
                                  baseHeight),
                        baseHeightColor
                    );
        normal = QVector3D::normal(v1.position(), v2.position(), v3.position());
        v1.setNormal(normal);
        v2.setNormal(normal);
        v3.setNormal(normal);
        demObject->addVertex(v1, demObject->getVertexPosition(0,i));
        demObject->addVertex(v2, demObject->getVertexPosition(0,i+step));
        demObject->addVertex(v3, demObject->getVertexPosition(0,i,1, demObject->DIRECTION_WEST));

        Vertex v4 = Vertex(
                        QVector3D(v2.position().x(), v2.position().y(), baseHeight),
                        baseHeightColor
                    );
        normal = QVector3D::normal(v2.position(), v3.position(), v4.position());
        v2.setNormal(normal);
        v3.setNormal(normal);
        v4.setNormal(normal);
        demObject->addVertex(v2, demObject->getVertexPosition(0, i+step));
        demObject->addVertex(v3, demObject->getVertexPosition(0, i, 1, demObject->DIRECTION_WEST));
        demObject->addVertex(v4, demObject->getVertexPosition(0, i+step, 1, demObject->DIRECTION_WEST));
    }

    for (int i=0; i<= demObject->getRows()-1 -step; i=i+step) {

        // Right
        v1 = demData[demObject->getVertexPosition(demObject->getCols()-1 - step, i)];
        v2 = demData[demObject->getVertexPosition(demObject->getCols()-1 - step,i + step)];

        v3 = Vertex(
                        QVector3D(v1.position().x(), v1.position().y(),
                                  baseHeight),
                        baseHeightColor
                    );
        normal = QVector3D::normal(v1.position(), v2.position(), v3.position());
        v1.setNormal(normal);
        v2.setNormal(normal);
        v3.setNormal(normal);
        demObject->addVertex(v1, demObject->getVertexPosition(demObject->getCols()-1 - step,i));
        demObject->addVertex(v2, demObject->getVertexPosition(demObject->getCols()-1 - step, i+step));
        demObject->addVertex(v3, demObject->getVertexPosition(demObject->getCols()-1 - step,i,1, demObject->DIRECTION_EAST));

        Vertex v4 = Vertex(
                        QVector3D(v2.position().x(), v2.position().y(), baseHeight),
                        baseHeightColor
                    );
        normal = QVector3D::normal(v2.position(), v3.position(), v4.position());
        v2.setNormal(normal);
        v3.setNormal(normal);
        v4.setNormal(normal);
        demObject->addVertex(v2, demObject->getVertexPosition(demObject->getCols()-1 - step, i+step));
        demObject->addVertex(v3, demObject->getVertexPosition(demObject->getCols()-1 - step, i, 1, demObject->DIRECTION_EAST));
        demObject->addVertex(v4, demObject->getVertexPosition(demObject->getCols()-1 - step, i+step, 1, demObject->DIRECTION_EAST));
    }
    // Top left
    int index1 = demObject->getVertexPosition(0,0,1, demObject->DIRECTION_NORTH);
    v1 = demData[index1];

    // Top right
    int index2 = demObject->getVertexPosition(demObject->getCols()-1-step,0,1, demObject->DIRECTION_NORTH);
    v2 = demData[index2];

    // Bottom left
    int index3 = demObject->getVertexPosition(0,demObject->getRows()-1-step,1, demObject->DIRECTION_SOUTH);
    v3 = demData[index3];

    normal = QVector3D::normal(v1.position(), v2.position(), v3.position());
    v1.setNormal(normal);
    v2.setNormal(normal);
    v3.setNormal(normal);
    demObject->addVertex(v1, index1 );
    demObject->addVertex(v2, index2 );
    demObject->addVertex(v3, index3 );

    // Bottom left
    index1 = demObject->getVertexPosition(0,demObject->getRows()-1-step,1, demObject->DIRECTION_SOUTH);
    v1 = demData[index1];

    // Top right
    index2 = demObject->getVertexPosition(demObject->getCols()-1-step,0,1, demObject->DIRECTION_NORTH);
    v2 = demData[index2];

    //Bottom right
    index3 = demObject->getVertexPosition(demObject->getCols() - 1-step, demObject->getRows()-1-step,1, demObject->DIRECTION_SOUTH);
    v3 = demData[index3];


    normal = QVector3D::normal(v1.position(), v2.position(), v3.position());
    v1.setNormal(normal);
    v2.setNormal(normal);
    v3.setNormal(normal);
    demObject->addVertex(v1, index1 );
    demObject->addVertex(v2, index2 );
    demObject->addVertex(v3, index3 );


}

void BaseSupportController::setActionPerform(ActionListener *actions)
{
    this->actions = actions;
}
