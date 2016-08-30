#include "filegraphics.h"
#include <QDebug>

FileGraphics::FileGraphics()
{

}

void FileGraphics::initial()
{
    fcontroller = (FileController*)getAction(QString("File.FileController"));
    colorController = (ColorController*)getAction(QString("Color.ColorController"));
    bsController = (BaseSupportController*)getAction(QString("BaseSupport.BaseSupportController"));
    QAction* action = createQAction(QString("Open DEM File"));
    addMenu(QString("File"), action);
    QIODevice::connect(action, &QAction::triggered, fcontroller, &FileController::openFile);
}

FileGraphics::~FileGraphics()
{
}

float FileGraphics::getZCoordinate(float height) {
    return fcontroller->getDemObject()->heightScale(height);
}

void FileGraphics::initializeGL()
{
    if (fcontroller->isOpenedFile())
    {
        int rows, cols;
        Vertex v1,v2,v3;
        QVector3D normal;
        DemInterface* demObject = fcontroller->getDemObject();
        cols = demObject->getCols();
        rows = demObject->getRows();
        int centerX = cols/2;
        float posX, posY = 0;
        scale = (float)getSize().width() / (float)cols;
        int centerY = rows/2;
        ColorRGBA color;
        std::vector<float> band_data = demObject->readDem();
        maxZ = demObject->maxHeight();
        int step = demObject->getZoom();

        for (int k = 0; k < rows; k=k+step) {
            posY = (float)(centerY - k)/centerY;
            for (int j =0; j < cols; j=j+step) {
                posX = (float)(j - centerX)/centerX;
                if (k < rows -step && j-step >= 0) {
                    color = colorController->getColor(band_data[k*rows + j]);
                    v1 = Vertex(
                                QVector3D(posX, posY, getZCoordinate(band_data[k*rows + j])),
                                QVector3D(color.r, color.g, color.b)
                            );


                    float nposY = (float)(centerY - (k +step))/centerY;
                    color = colorController->getColor(band_data[(k+step)*rows + j]);
                    v2 = Vertex(
                                QVector3D(posX, nposY, getZCoordinate(band_data[(k+step)*rows + j])),
                                QVector3D(color.r, color.g, color.b)
                            );


                    float nposX = (float)(j - step - centerX)/centerX;
                    color = colorController->getColor(band_data[k*rows + j - step]);
                    v3 = Vertex(
                                QVector3D(nposX, posY, getZCoordinate(band_data[k*rows + j - step])),
                                QVector3D(color.r, color.g, color.b)
                            );
                    normal = QVector3D::normal(v1.position(), v2.position(), v3.position());
                    v1.setNormal(normal);
                    v2.setNormal(normal);
                    v3.setNormal(normal);
                    addVertex(v1, j, k);
                    addVertex(v2, j, k+step);
                    addVertex(v3, j -step, k);
                }
                if (k - step >= 0 && j < cols -step) {
                    color = colorController->getColor(band_data[k*rows + j]);
                    v1 = Vertex(
                                QVector3D(posX, posY, getZCoordinate(band_data[k*rows + j])),
                                QVector3D(color.r, color.g, color.b)
                            );

                    float nposY = (float)(centerY - (k -step))/centerY;
                    color = colorController->getColor(band_data[(k-step)*rows + j]);
                    v2 = Vertex(
                                QVector3D(posX, nposY, getZCoordinate(band_data[(k-step)*rows + j])),
                                QVector3D(color.r, color.g, color.b)
                            );

                    float nposX = (float)(j +step - centerX)/centerX;
                    color = colorController->getColor(band_data[k*rows + j+step]);
                    v3 = Vertex(
                                QVector3D(nposX, posY, getZCoordinate(band_data[k*rows + j+step])),
                                QVector3D(color.r, color.g, color.b)
                            );
                    normal = QVector3D::normal(v1.position(), v2.position(), v3.position());
                    v1.setNormal(normal);
                    v2.setNormal(normal);
                    v3.setNormal(normal);
                    addVertex(v1, j, k);
                    addVertex(v2, j, k- step);
                    addVertex(v3, j+step, k);
                }

            }
        }
        bsController->generateBaseSupport();
    }
}

void FileGraphics::paintGL()
{            

}
void FileGraphics::resizeGL(int , int )
{

}
