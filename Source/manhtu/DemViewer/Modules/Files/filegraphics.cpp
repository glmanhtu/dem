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
        GDALDataset* pDataset = fcontroller->getDemObject()->getDataSet();
        cols = pDataset->GetRasterXSize();
        rows = pDataset->GetRasterYSize();
        double transform[6];
        pDataset->GetGeoTransform(transform);

        // Fetch the band
        GDALRasterBand* band = pDataset->GetRasterBand(1);
        std::vector<float> band_data(cols*rows);

        // Read the data
        band->RasterIO( GF_Read, 0, 0,
                        cols, rows,
                        band_data.data(),
                        cols, rows,
                        GDT_Float32,
                        0, 0);

            int centerX = cols/2;
            float posX, posY = 0;
            scale = getSize().width() / cols;
            int centerY = rows/2;
            ColorRGBA color;
            maxZ = *std::max_element(band_data.begin(), band_data.end());
            fcontroller->getDemObject()->setMaxHeight(maxZ);
            int minZ = *std::min_element(band_data.begin(), band_data.end());
            fcontroller->getDemObject()->setMinHeight(minZ);
            int step = 2;
            for (int k = 0; k < rows; k=k+step) {
                posY = (float)(centerY - k)/centerY;
                for (int j =0; j < cols; j=j+step) {

                    posX = (float)(j - centerX)/centerX;
                    if (k - step >= 0 && j-step >= 0) {
                        color = colorController->getColor(band_data[k*rows + j]);
                        addVertex(
                                    Vertex(
                                        QVector3D(posX, posY, getZCoordinate(band_data[k*rows + j])),
                                        QVector3D(color.r, color.g, color.b)
                                    )
                                );

                        float nposY = (float)(centerY - (k -step))/centerY;
                        color = colorController->getColor(band_data[(k-step)*rows + j]);
                        addVertex(
                                    Vertex(
                                        QVector3D(posX, nposY, getZCoordinate(band_data[(k-step)*rows + j])),
                                        QVector3D(color.r, color.g, color.b)
                                    )
                                );

                        float nposX = (float)(j - step - centerX)/centerX;
                        color = colorController->getColor(band_data[k*rows + j - step]);
                        addVertex(
                                    Vertex(
                                        QVector3D(nposX, posY, getZCoordinate(band_data[k*rows + j - step])),
                                        QVector3D(color.r, color.g, color.b)
                                    )
                                );
                    }
                    if (k < rows -step && j < cols -step) {
                        color = colorController->getColor(band_data[k*rows + j]);
                        addVertex(
                                    Vertex(
                                        QVector3D(posX, posY, getZCoordinate(band_data[k*rows + j])),
                                        QVector3D(color.r, color.g, color.b)
                                    )
                                );

                        float nposY = (float)(centerY - (k +step))/centerY;
                        color = colorController->getColor(band_data[(k+step)*rows + j]);
                        addVertex(
                                    Vertex(
                                        QVector3D(posX, nposY, getZCoordinate(band_data[(k+step)*rows + j])),
                                        QVector3D(color.r, color.g, color.b)
                                    )
                                );

                        float nposX = (float)(j +step - centerX)/centerX;
                        color = colorController->getColor(band_data[k*rows + j+step]);
                        addVertex(
                                    Vertex(
                                        QVector3D(nposX, posY, getZCoordinate(band_data[k*rows + j+step])),
                                        QVector3D(color.r, color.g, color.b)
                                    )
                                );
                    }

                }
            }
        bsController->generateBaseSupport();
    }
}

float* getNormal(float* p1, float* p2, float* p3)
{
    float *u = new float[3];
    u[0] = p2[0] - p1[0];
    u[1] = p2[1] - p1[1];
    u[2] = p2[2] - p1[2];

    float*v = new float[3];
    v[0] = p3[0] - p1[0];
    v[1] = p3[1] - p1[1];
    v[2] = p3[2] - p1[2];

    float* result = new float[3];
    result[0] = u[1] * v[2] - u[2] * v[1];
    result[1] = u[2] * v[0] - u[0] * v[2];
    result[2] = u[0] * v[1] - u[1] * v[0];
    delete[] v;
    delete[] u;
    return result;
}

void FileGraphics::paintGL()
{            

}
void FileGraphics::resizeGL(int width, int height)
{

}
