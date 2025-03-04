#include "filegraphics.h"
#include <QDebug>

FileGraphics::FileGraphics()
{
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

void FileGraphics::initializeGL()
{

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

ColorRGBA getColor(unsigned char const * const p) {
    ColorRGBA* c = new ColorRGBA();
    c->r = p[0];
    c->g = p[1];
    c->b = p[2];
    c->a = p[3];
    return *c;
}

void FileGraphics::paintGL()
{

//    float data[12][3] = {
//        {-1, -1, 0},
//        {1, -1, 0},
//        {0,0,1.2},
//        {1,-1,0},
//        {1,1,0},
//        {0,0,1.2},
//        {1,1,0},
//        {-1,1,0},
//        {0,0,1.2},
//        {-1,1,0},
//        {-1,-1,0},
//        {0,0,1.2}
//    };

//    glBegin(GL_TRIANGLES);
//        for (int i=0; i< 12; i=i+3) {
//            float *rs1 = getNormal(data[i], data[i+1], data[i+2]);
//            glNormal3f(rs1[0], rs1[1], rs1[2]);
//            glVertex3f(data[i][0], data[i][1], data[i][2]);
//            glVertex3f(data[i+1][0], data[i+1][1], data[i+1][2]);
//            glVertex3f(data[i+2][0], data[i+2][1], data[i+2][2]);
//        }
//    glEnd();

    if (fcontroller->getDemObject() != NULL)
    {
        int rows, cols;
        GDALDataset* pDataset = fcontroller->getDemObject()->getDataSet();
        cols = pDataset->GetRasterXSize();
        rows = pDataset->GetRasterYSize();
        setSize(900, 600);

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

        glBegin(GL_TRIANGLES);

        int centerX = cols/2;
        float posX, posY, posZ = 0;
        int centerY = rows/2;
        float maxZ = *std::max_element(band_data.begin(), band_data.end());
        ColorRGBA color;
        for (int k = 0; k < rows; k++) {
            posY = (float)(centerY - k)/centerY;
            for (int j =0; j < cols; j++) {

                posX = (float)(j - centerX)/centerX;
                posZ = (float)band_data[k*rows + j] / maxZ;
                if (k > 0 && j > 0) {
                    color = getColor((unsigned char const *)&band_data[k*rows + j]);
                    glColor3f(color.r/255.0,color.g/255.0,color.b/255.0);
                    glVertex3f(posX, posY, posZ);


                    float nposY = (float)(centerY - (k -1))/centerY;
                    float nposZ = (float)band_data[(k-1)*rows + j] / maxZ;
                    color = getColor((unsigned char const *)&band_data[(k-1)*rows + j]);
                    glColor3f(color.r/255.0,color.g/255.0,color.b/255.0);
                    glVertex3f(posX, nposY, nposZ);

                    float nposX = (float)(j -1 - centerX)/centerX;
                    nposZ = (float)band_data[k*rows + j -1] / maxZ;
                    color = getColor((unsigned char const *)&band_data[k*rows + j - 1]);
                    glColor3f(color.r/255.0,color.g/255.0,color.b/255.0);
                    glVertex3f(nposX, posY, nposZ);
                }
                if (k < rows -1 && j < cols -1) {
                    color = getColor((unsigned char const *)&band_data[k*rows + j]);
                    glColor3f(color.r/255.0,color.g/255.0,color.b/255.0);
                    glVertex3f(posX, posY, posZ);

                    float nposY = (float)(centerY - (k +1))/centerY;
                    float nposZ = (float)band_data[(k+1)*rows + j] / maxZ;
                    color = getColor((unsigned char const *)&band_data[(k+1)*rows + j]);
                    glColor3f(color.r/255.0,color.g/255.0,color.b/255.0);
                    glVertex3f(posX, nposY, nposZ);

                    float nposX = (float)(j +1 - centerX)/centerX;
                    nposZ = (float)band_data[(k)*rows + j +1] / maxZ;
                    color = getColor((unsigned char const *)&band_data[k*rows + j+1]);
                    glColor3f(color.r/255.0,color.g/255.0,color.b/255.0);
                    glVertex3f(nposX, posY, nposZ);
                }

                if (k < rows -1 && j >0) {
                    color = getColor((unsigned char const *)&band_data[k*rows + j]);
                    glColor3f(color.r/255.0,color.g/255.0,color.b/255.0);
                    glVertex3f(posX, posY, posZ);

                    float nposY = (float)(centerY - (k +1))/centerY;
                    float nposZ = (float)band_data[(k+1)*rows + j] / maxZ;
                    color = getColor((unsigned char const *)&band_data[(k+1)*rows + j]);
                    glColor3f(color.r/255.0,color.g/255.0,color.b/255.0);
                    glVertex3f(posX, nposY, nposZ);

                    float nposX = (float)(j -1 - centerX)/centerX;
                    nposZ = (float)band_data[(k)*rows + j -1] / maxZ;
                    color = getColor((unsigned char const *)&band_data[k*rows + j-1]);
                    glColor3f(color.r/255.0,color.g/255.0,color.b/255.0);
                    glVertex3f(nposX, posY, nposZ);
                }

                if (k > 0 && j < cols -1) {
                    color = getColor((unsigned char const *)&band_data[k*rows + j]);
                    glColor3f(color.r/255.0,color.g/255.0,color.b/255.0);
                    glVertex3f(posX, posY, posZ);

                    float nposY = (float)(centerY - (k -1))/centerY;
                    float nposZ = (float)band_data[(k-1)*rows + j] / maxZ;
                    color = getColor((unsigned char const *)&band_data[(k-1)*rows + j]);
                    glColor3f(color.r/255.0,color.g/255.0,color.b/255.0);
                    glVertex3f(posX, nposY, nposZ);

                    float nposX = (float)(j +1 - centerX)/centerX;
                    nposZ = (float)band_data[(k)*rows + j +1] / maxZ;
                    color = getColor((unsigned char const *)&band_data[k*rows + j+1]);
                    glColor3f(color.r/255.0,color.g/255.0,color.b/255.0);
                    glVertex3f(nposX, posY, nposZ);
                }

            }
        }
        glEnd( );
    }
}
void FileGraphics::resizeGL(int width, int height)
{

}
