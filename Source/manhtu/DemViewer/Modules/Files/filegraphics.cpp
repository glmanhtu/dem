#include "filegraphics.h"
#include <QDebug>

FileGraphics::FileGraphics()
{
    addColor(ColorRGBA(25,0,40), ColorRGBA(35,0,58), 4000);
    addColor(ColorRGBA(35,0,58), ColorRGBA(20,0,75), 2000);
    addColor(ColorRGBA(20,0,75), ColorRGBA(6,0,111), 2000);
    addColor(ColorRGBA(6,0,111), ColorRGBA(0,19,156), 1000);
    addColor(ColorRGBA(0,19,156), ColorRGBA(6,60,166), 1000);
    addColor(ColorRGBA(6,60,166), ColorRGBA(21,100,171), 850);
    addColor(ColorRGBA(21,100,171), ColorRGBA(51,147,201), 100);
    addColor(ColorRGBA(51,147,201), ColorRGBA(71,183,190), 30);
    addColor(ColorRGBA(71,183,190), ColorRGBA(103,186,191), 15);
    addColor(ColorRGBA(103,186,191), ColorRGBA(131,193,196), 5);

    addColor(ColorRGBA(31,83,54), ColorRGBA(26,103,37), 10);
    addColor(ColorRGBA(26,103,37), ColorRGBA(181,171,88), 490);
    addColor(ColorRGBA(181,171,88), ColorRGBA(145,57,9), 1500);
    addColor(ColorRGBA(145,57,9), ColorRGBA(130,0,1), 1000);
    addColor(ColorRGBA(130,0,1), ColorRGBA(91,85,85), 2000);
    addColor(ColorRGBA(91,85,85), ColorRGBA(223,223,223), 2500);
    addColor(ColorRGBA(223,223,223), ColorRGBA(255,255,255), 1500);
}

void FileGraphics::addColor(ColorRGBA color1, ColorRGBA color2, int step)
{
    float interval_R = (float)(color2.red() - color1.red()) / step;
    float interval_G = (float)(color2.green() - color1.green()) / step;
    float interval_B = (float)(color2.blue() - color1.blue()) / step;

    float current_R = color1.red();
    float current_G = color1.green();
    float current_B = color1.blue();

    data_colors.push_back(color1);
    for (int i = 0; i <= step; i++)
    {
        current_R += interval_R;
        current_G += interval_G;
        current_B += interval_B;
        data_colors.push_back(ColorRGBA(current_R, current_G, current_B));
    }
    data_colors.push_back(color2);
}


void FileGraphics::initial()
{
    fcontroller = (FileController*)getAction(QString("File.FileController"));
    QAction* action = createQAction(QString("Open DEM File"));
    addMenu(QString("File"), action);
    QIODevice::connect(action, &QAction::triggered, fcontroller, &FileController::openFile);
}

FileGraphics::~FileGraphics()
{
}

ColorRGBA FileGraphics::getColor(float height) {

    ColorRGBA* c = new ColorRGBA();
    ColorRGBA color = data_colors[height+11000];
    c->r = color.red()/255;
    c->g = color.green()/255;
    c->b = color.blue()/255;
    return *c;
}

float FileGraphics::getZCoordinate(float height) {
    return (height/9000);
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
            int step = 2;
            for (int k = 0; k < rows; k=k+step) {
                posY = (float)(centerY - k)/centerY;
                for (int j =0; j < cols; j=j+step) {

                    posX = (float)(j - centerX)/centerX;
                    if (k - step >= 0 && j-step >= 0) {
                        color = getColor(band_data[k*rows + j]);
                        addVertex(
                                    Vertex(
                                        QVector3D(posX, posY, getZCoordinate(band_data[k*rows + j])),
                                        QVector3D(color.r, color.g, color.b)
                                    )
                                );

                        float nposY = (float)(centerY - (k -step))/centerY;
                        color = getColor(band_data[(k-step)*rows + j]);
                        addVertex(
                                    Vertex(
                                        QVector3D(posX, nposY, getZCoordinate(band_data[(k-step)*rows + j])),
                                        QVector3D(color.r, color.g, color.b)
                                    )
                                );

                        float nposX = (float)(j - step - centerX)/centerX;
                        color = getColor(band_data[k*rows + j - step]);
                        addVertex(
                                    Vertex(
                                        QVector3D(nposX, posY, getZCoordinate(band_data[k*rows + j - step])),
                                        QVector3D(color.r, color.g, color.b)
                                    )
                                );
                    }
                    if (k < rows -step && j < cols -step) {
                        color = getColor(band_data[k*rows + j]);
                        addVertex(
                                    Vertex(
                                        QVector3D(posX, posY, getZCoordinate(band_data[k*rows + j])),
                                        QVector3D(color.r, color.g, color.b)
                                    )
                                );

                        float nposY = (float)(centerY - (k +step))/centerY;
                        color = getColor(band_data[(k+step)*rows + j]);
                        addVertex(
                                    Vertex(
                                        QVector3D(posX, nposY, getZCoordinate(band_data[(k+step)*rows + j])),
                                        QVector3D(color.r, color.g, color.b)
                                    )
                                );

                        float nposX = (float)(j +step - centerX)/centerX;
                        color = getColor(band_data[k*rows + j+step]);
                        addVertex(
                                    Vertex(
                                        QVector3D(nposX, posY, getZCoordinate(band_data[k*rows + j+step])),
                                        QVector3D(color.r, color.g, color.b)
                                    )
                                );
                    }

//                    if (k < rows -1 && j >0) {
//                        color = getColor(band_data[k*rows + j]);
//                        glColor4d(color.r,color.g,color.b, color.a/255.0);
//                        addVertex(
//                                    Vertex(
//                                        QVector3D(posX, posY, posZ),
//                                        QVector3D(color.r, color.g, color.b)
//                                    )
//                                );

//                        float nposY = (float)(centerY - (k +1))/centerY;
//                        float nposZ = (float)band_data[(k+1)*rows + j] / maxZ;
//                        color = getColor(band_data[(k+1)*rows + j]);
//                        addVertex(
//                                    Vertex(
//                                        QVector3D(posX, nposY, nposZ),
//                                        QVector3D(color.r, color.g, color.b)
//                                    )
//                                );

//                        float nposX = (float)(j -1 - centerX)/centerX;
//                        nposZ = (float)band_data[(k)*rows + j -1] / maxZ;
//                        color = getColor(band_data[k*rows + j-1]);
//                        addVertex(
//                                    Vertex(
//                                        QVector3D(nposX, posY, nposZ),
//                                        QVector3D(color.r, color.g, color.b)
//                                    )
//                                );
//                    }

//                    if (k > 0 && j < cols -1) {
//                        color = getColor(band_data[k*rows + j]);
//                        addVertex(
//                                                            Vertex(
//                                                                QVector3D(posX, posY, posZ),
//                                                                QVector3D(color.r, color.g, color.b)
//                                                            )
//                                                        );

//                        float nposY = (float)(centerY - (k -1))/centerY;
//                        float nposZ = (float)band_data[(k-1)*rows + j] / maxZ;
//                        color = getColor(band_data[(k-1)*rows + j]);
//                        addVertex(
//                                                            Vertex(
//                                                                QVector3D(posX, nposY, nposZ),
//                                                                QVector3D(color.r, color.g, color.b)
//                                                            )
//                                                        );

//                        float nposX = (float)(j +1 - centerX)/centerX;
//                        nposZ = (float)band_data[(k)*rows + j +1] / maxZ;
//                        color = getColor(band_data[k*rows + j+1]);
//                        addVertex(
//                                                            Vertex(
//                                                                QVector3D(nposX, posY, nposZ),
//                                                                QVector3D(color.r, color.g, color.b)
//                                                            )
//                                                        );
//                    }

                }
            }
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
