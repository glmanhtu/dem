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
    baseHeight = demObject->heightScale(demObject->minHeight() - 500);
    int step = demObject->getZoom();
    ColorController* colorController = (ColorController*)actions->getAction(QString("Color.ColorController"));
    QVector3D baseHeightColor = colorController->getVectorColor(baseHeight);
    Vertex* demData = demObject->getArrayVertexs();
    for (int i=0; i<= demObject->getCols()-1; i=i+step) {

        // Top
        Vertex v1 = demData[demObject->getVertexPosition(i,0)];
        Vertex v2 = demData[demObject->getVertexPosition(i+step,0)];

        Vertex v3 = Vertex(
                        QVector3D(v1.position().x(), v1.position().y(),
                                  baseHeight),
                        baseHeightColor
                    );
        demObject->addVertex(v1, demObject->getVertexPosition(i,0));
        demObject->addVertex(v2, demObject->getVertexPosition(i+step,0));
        demObject->addVertex(v3, demObject->getVertexPosition(i,0,1,demObject->DIRECTION_NORTH));

        Vertex v4 = Vertex(
                        QVector3D(v2.position().x(), v2.position().y(), baseHeight),
                        baseHeightColor
                    );
        demObject->addVertex(v2, demObject->getVertexPosition(i+step, 0));
        demObject->addVertex(v3, demObject->getVertexPosition(i,0, 1, demObject->DIRECTION_NORTH));
        demObject->addVertex(v4, demObject->getVertexPosition(i+step,0, 1, demObject->DIRECTION_NORTH));
    }

    for (int i=0; i< demObject->getCols() - 1; i= i+ step) {
        // Bottom
        Vertex v1 = demData[demObject->getVertexPosition(i,demObject->getRows()-1)];
        Vertex v2 = demData[demObject->getVertexPosition(i+step,demObject->getRows()-1)];

        Vertex v3 = Vertex(
                        QVector3D(v1.position().x(), v1.position().y(),
                                  baseHeight),
                        baseHeightColor
                    );
        demObject->addVertex(v1, demObject->getVertexPosition(i,demObject->getRows()-1));
        demObject->addVertex(v2, demObject->getVertexPosition(i+step,demObject->getRows()-1));
        demObject->addVertex(v3, demObject->getVertexPosition(i,demObject->getRows()-1,1, demObject->DIRECTION_SOUTH));

        Vertex v4 = Vertex(
                        QVector3D(v2.position().x(), v2.position().y(), baseHeight),
                        baseHeightColor
                    );
        demObject->addVertex(v2, demObject->getVertexPosition(i+step, demObject->getRows()-1));
        demObject->addVertex(v3, demObject->getVertexPosition(i,demObject->getRows()-1, 1, demObject->DIRECTION_SOUTH));
        demObject->addVertex(v4, demObject->getVertexPosition(i+step,demObject->getRows()-1, 1, demObject->DIRECTION_SOUTH));
    }

    for (int i=0; i<= demObject->getRows()-1; i=i+step) {

        // Left
        Vertex v1 = demData[demObject->getVertexPosition(0, i)];
        Vertex v2 = demData[demObject->getVertexPosition(0,i + step)];

        Vertex v3 = Vertex(
                        QVector3D(v1.position().x(), v1.position().y(),
                                  baseHeight),
                        baseHeightColor
                    );
        demObject->addVertex(v1, demObject->getVertexPosition(0,i));
        demObject->addVertex(v2, demObject->getVertexPosition(0,i+step));
        demObject->addVertex(v3, demObject->getVertexPosition(0,i,1, demObject->DIRECTION_WEST));

        Vertex v4 = Vertex(
                        QVector3D(v2.position().x(), v2.position().y(), baseHeight),
                        baseHeightColor
                    );
        demObject->addVertex(v2, demObject->getVertexPosition(0, i+step));
        demObject->addVertex(v3, demObject->getVertexPosition(0, i, 1, demObject->DIRECTION_WEST));
        demObject->addVertex(v4, demObject->getVertexPosition(0, i+step, 1, demObject->DIRECTION_WEST));
    }

    for (int i=0; i<= demObject->getRows()-1; i=i+step) {

        // Right
        Vertex v1 = demData[demObject->getVertexPosition(demObject->getCols()-1, i)];
        Vertex v2 = demData[demObject->getVertexPosition(demObject->getCols()-1,i + step)];

        Vertex v3 = Vertex(
                        QVector3D(v1.position().x(), v1.position().y(),
                                  baseHeight),
                        baseHeightColor
                    );
        demObject->addVertex(v1, demObject->getVertexPosition(demObject->getCols()-1,i));
        demObject->addVertex(v2, demObject->getVertexPosition(demObject->getCols()-1, i+step));
        demObject->addVertex(v3, demObject->getVertexPosition(demObject->getCols()-1,i,1, demObject->DIRECTION_EAST));

        Vertex v4 = Vertex(
                        QVector3D(v2.position().x(), v2.position().y(), baseHeight),
                        baseHeightColor
                    );
        demObject->addVertex(v2, demObject->getVertexPosition(demObject->getCols()-1, i+step));
        demObject->addVertex(v3, demObject->getVertexPosition(demObject->getCols()-1, i, 1, demObject->DIRECTION_EAST));
        demObject->addVertex(v4, demObject->getVertexPosition(demObject->getCols()-1, i+step, 1, demObject->DIRECTION_EAST));
    }
    // Top left
    int index = demObject->getVertexPosition(0,0,1, demObject->DIRECTION_NORTH);
    demObject->addVertex( demData[index], index );
    // Top right
    index = demObject->getVertexPosition(demObject->getCols()-1,0,1, demObject->DIRECTION_EAST);
    demObject->addVertex( demData[index], index );
    // Bottom left
    index = demObject->getVertexPosition(0,demObject->getRows()-1,1, demObject->DIRECTION_SOUTH);
    demObject->addVertex( demData[index], index );

    // Bottom left
    index = demObject->getVertexPosition(0,demObject->getRows()-1,1, demObject->DIRECTION_SOUTH);
    demObject->addVertex( demData[index], index );

    // Top right
    index = demObject->getVertexPosition(demObject->getCols()-1,0,1, demObject->DIRECTION_EAST);
    demObject->addVertex( demData[index], index );

    //Bottom right
    index = demObject->getVertexPosition(demObject->getCols() - 1, demObject->getRows()-1,1, demObject->DIRECTION_SOUTH);
    demObject->addVertex( demData[index], index );



}

void BaseSupportController::generateTriangleInSide(int x, int y, ColorController *colorController, Vertex *vertexs)
{
//    float tempZ = -11000;
//    demObject->addVertex(
//        Vertex(
//            v1.position(),
//            v1.color()
//        )
//    );
//    demObject->addVertex(
//        Vertex(
//            v2.position(),
//            v2.color()
//        )
//    );
//    if (v1.position().z() > v2.position().z()) {
//        color1 = v2.color();
//        demObject->addVertex(
//            Vertex(
//                QVector3D(v1.position().x(), v1.position().y(), v2.position().z()),
//                color1
//            )
//        );
//        tempZ = v2.position().z();
//    } else {
//        color1 = v1.color();
//        demObject->addVertex(
//            Vertex(
//                QVector3D(v2.position().x(), v2.position().y(), v1.position().z()),
//                color1
//            )
//        );
//        tempZ = v1.position().z();
//    }

//    float scaledMinHeight = demObject->heightScale(demObject->minHeight());
//    if (tempZ > scaledMinHeight) {
//        color2 = colorController->getVectorColor(demObject->minHeight());
//        demObject->addVertex(
//            Vertex(
//                QVector3D(v1.position().x(), v1.position().y(), tempZ),
//                color1
//            )
//        );
//        demObject->addVertex(
//            Vertex(
//                QVector3D(v2.position().x(), v2.position().y(), tempZ),
//                color1
//            )
//        );
//        demObject->addVertex(
//            Vertex(
//                QVector3D(v2.position().x(), v2.position().y(), scaledMinHeight),
//                color2
//            )
//        );
//        demObject->addVertex(
//            Vertex(
//                QVector3D(v1.position().x(), v1.position().y(), scaledMinHeight),
//                color2
//            )
//        );
//        demObject->addVertex(
//            Vertex(
//                QVector3D(v2.position().x(), v2.position().y(), scaledMinHeight),
//                color2
//            )
//        );
//        demObject->addVertex(
//            Vertex(
//                QVector3D(v1.position().x(), v1.position().y(), tempZ),
//                color1
//            )
//        );
//    }

//    color1 = colorController->getVectorColor(demObject->minHeight());
//    demObject->addVertex(
//        Vertex(
//            QVector3D(v1.position().x(), v1.position().y(), baseHeight),
//            color1
//        )
//    );
//    demObject->addVertex(
//        Vertex(
//            QVector3D(v2.position().x(), v2.position().y(), baseHeight),
//            color1
//        )
//    );
//    demObject->addVertex(
//        Vertex(
//            QVector3D(v2.position().x(), v2.position().y(), scaledMinHeight),
//            color2
//        )
//    );
//    demObject->addVertex(
//        Vertex(
//            QVector3D(v1.position().x(), v1.position().y(), scaledMinHeight),
//            color2
//        )
//    );
//    demObject->addVertex(
//        Vertex(
//            QVector3D(v2.position().x(), v2.position().y(), scaledMinHeight),
//            color2
//        )
//    );
//    demObject->addVertex(
//        Vertex(
//            QVector3D(v1.position().x(), v1.position().y(), baseHeight),
//            color1
//        )
//    );
}

void BaseSupportController::setActionPerform(ActionListener *actions)
{
    this->actions = actions;
}
