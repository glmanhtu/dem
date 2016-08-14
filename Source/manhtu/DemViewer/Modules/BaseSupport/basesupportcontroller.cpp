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
    baseHeight = demObject->heightScale(demObject->minHeight() - demObject->maxHeight()/6);
    int step = 2;
    ColorController* colorController = (ColorController*)actions->getAction(QString("Color.ColorController"));    
    Vertex* demData = demObject->getArrayVertexs();
    for (int i=0; i<demObject->getCols(); i=i+step) {
        int index = demObject->getVertexPositionIn2D(i, 0, true);
        generateTriangleInSide(index, colorController, demObject->getArrayVertexs(), false);
        index = demObject->getVertexPositionIn2D(i, demObject->getRows() - 1, false);
        generateTriangleInSide(index, colorController, demObject->getArrayVertexs(), false);
    }

    for (int i=0; i<demObject->getRows(); i=i+step) {
        int index = demObject->getVertexPositionIn2D(0, i, false);
        generateTriangleInSide(index, colorController, demObject->getArrayVertexs(), true);
        index = demObject->getVertexPositionIn2D(demObject->getCols() - 1 - step, i, true);
        generateTriangleInSide(index, colorController, demObject->getArrayVertexs(), true);
    }
    demObject->addVertex(
        Vertex(
            QVector3D(demData[2].position().x(), demData[2].position().y(), baseHeight),
            color1
        )
    );
    int index = demObject->getVertexPositionIn2D(demObject->getCols() - 1 - step, 0, true);
    demObject->addVertex(
        Vertex(
            QVector3D(demData[index].position().x(), demData[index].position().y(), baseHeight),
            color1
        )
    );
    index = demObject->getVertexPositionIn2D(0, demObject->getRows() - 1 - step, false);
    demObject->addVertex(
        Vertex(
            QVector3D(demData[index].position().x(), demData[index].position().y(), baseHeight),
            color1
        )
    );

//    demObject->addVertex(
//        Vertex(
//            QVector3D(demData[index].position().x(), demData[index].position().y(), baseHeight),
//            color1
//        )
//    );

//    index = demObject->getVertexPositionIn2D(demObject->getCols() - 1 - step, demObject->getRows() - 1 - step, true);
//    demObject->addVertex(
//        Vertex(
//            QVector3D(demData[index+1].position().x(), demData[index+1].position().y(), baseHeight),
//            color1
//        )
//    );
//    index = demObject->getVertexPositionIn2D(demObject->getCols() - 1 - step, 0, true);
//        demObject->addVertex(
//            Vertex(
//                QVector3D(demData[index].position().x(), demData[index].position().y(), baseHeight),
//                color1
//            )
//        );

}

void BaseSupportController::generateTriangleInSide(int index, ColorController *colorController, Vertex *vertexs, bool northsouth)
{
    float tempZ = -11000;
    Vertex v1, v2;
    v1.setColor(vertexs[index].color());
    v1.setPosition(vertexs[index].position());
    if (northsouth) {
        v2.setColor(vertexs[index+1].color());
        v2.setPosition(vertexs[index+1].position());
    } else {
        v2.setColor(vertexs[index+2].color());
        v2.setPosition(vertexs[index+2].position());
    }
    demObject->addVertex(
        Vertex(
            v1.position(),
            v1.color()
        )
    );
    demObject->addVertex(
        Vertex(
            v2.position(),
            v2.color()
        )
    );
    if (v1.position().z() > v2.position().z()) {
        color1 = v2.color();
        demObject->addVertex(
            Vertex(
                QVector3D(v1.position().x(), v1.position().y(), v2.position().z()),
                color1
            )
        );
        tempZ = v2.position().z();
    } else {
        color1 = v1.color();
        demObject->addVertex(
            Vertex(
                QVector3D(v2.position().x(), v2.position().y(), v1.position().z()),
                color1
            )
        );
        tempZ = v1.position().z();
    }

    float scaledMinHeight = demObject->heightScale(demObject->minHeight());
    if (tempZ > scaledMinHeight) {
        color2 = colorController->getVectorColor(demObject->minHeight());
        demObject->addVertex(
            Vertex(
                QVector3D(v1.position().x(), v1.position().y(), tempZ),
                color1
            )
        );
        demObject->addVertex(
            Vertex(
                QVector3D(v2.position().x(), v2.position().y(), tempZ),
                color1
            )
        );
        demObject->addVertex(
            Vertex(
                QVector3D(v2.position().x(), v2.position().y(), scaledMinHeight),
                color2
            )
        );
        demObject->addVertex(
            Vertex(
                QVector3D(v1.position().x(), v1.position().y(), scaledMinHeight),
                color2
            )
        );
        demObject->addVertex(
            Vertex(
                QVector3D(v2.position().x(), v2.position().y(), scaledMinHeight),
                color2
            )
        );
        demObject->addVertex(
            Vertex(
                QVector3D(v1.position().x(), v1.position().y(), tempZ),
                color1
            )
        );
    }

    color1 = colorController->getVectorColor(demObject->minHeight());
    demObject->addVertex(
        Vertex(
            QVector3D(v1.position().x(), v1.position().y(), baseHeight),
            color1
        )
    );
    demObject->addVertex(
        Vertex(
            QVector3D(v2.position().x(), v2.position().y(), baseHeight),
            color1
        )
    );
    demObject->addVertex(
        Vertex(
            QVector3D(v2.position().x(), v2.position().y(), scaledMinHeight),
            color2
        )
    );
    demObject->addVertex(
        Vertex(
            QVector3D(v1.position().x(), v1.position().y(), scaledMinHeight),
            color2
        )
    );
    demObject->addVertex(
        Vertex(
            QVector3D(v2.position().x(), v2.position().y(), scaledMinHeight),
            color2
        )
    );
    demObject->addVertex(
        Vertex(
            QVector3D(v1.position().x(), v1.position().y(), baseHeight),
            color1
        )
    );
}

void BaseSupportController::setActionPerform(ActionListener *actions)
{
    this->actions = actions;
}
