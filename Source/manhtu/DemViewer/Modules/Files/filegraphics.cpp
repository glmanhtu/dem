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

ColorRGBA getColor(unsigned char const * const p) {
    ColorRGBA* c = new ColorRGBA();
    c->r = p[0];
    c->g = p[1];
    c->b = p[2];
    c->a = p[3];
    return *c;
}

void FileGraphics::addVertex(Vertex vertex)
{
    //data_vertex.push_back(vertex);
    data_paint.push_back(vertex.position().x());
    data_paint.push_back(vertex.position().y());
    data_paint.push_back(vertex.position().z());
    data_paint.push_back(vertex.color().x());
    data_paint.push_back(vertex.color().y());
    data_paint.push_back(vertex.color().z());
}

void FileGraphics::initializeGL()
{
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
                        addVertex(
                                    Vertex(
                                        QVector3D(posX, posY, posZ),
                                        QVector3D(color.r/255.0, color.g/255.0, color.b/255.0)
                                    )
                                );

                        float nposY = (float)(centerY - (k -1))/centerY;
                        float nposZ = (float)band_data[(k-1)*rows + j] / maxZ;
                        color = getColor((unsigned char const *)&band_data[(k-1)*rows + j]);                        
                        addVertex(
                                    Vertex(
                                        QVector3D(posX, nposY, nposZ),
                                        QVector3D(color.r/255.0, color.g/255.0, color.b/255.0)
                                    )
                                );

                        float nposX = (float)(j -1 - centerX)/centerX;
                        nposZ = (float)band_data[k*rows + j -1] / maxZ;
                        color = getColor((unsigned char const *)&band_data[k*rows + j - 1]);
                        addVertex(
                                    Vertex(
                                        QVector3D(nposX, posY, nposZ),
                                        QVector3D(color.r/255.0, color.g/255.0, color.b/255.0)
                                    )
                                );
                    }
                    if (k < rows -1 && j < cols -1) {
                        color = getColor((unsigned char const *)&band_data[k*rows + j]);                        
                        addVertex(
                                    Vertex(
                                        QVector3D(posX, posY, posZ),
                                        QVector3D(color.r/255.0, color.g/255.0, color.b/255.0)
                                    )
                                );

                        float nposY = (float)(centerY - (k +1))/centerY;
                        float nposZ = (float)band_data[(k+1)*rows + j] / maxZ;
                        color = getColor((unsigned char const *)&band_data[(k+1)*rows + j]);
                        addVertex(
                                    Vertex(
                                        QVector3D(posX, nposY, nposZ),
                                        QVector3D(color.r/255.0, color.g/255.0, color.b/255.0)
                                    )
                                );

                        float nposX = (float)(j +1 - centerX)/centerX;
                        nposZ = (float)band_data[(k)*rows + j +1] / maxZ;
                        color = getColor((unsigned char const *)&band_data[k*rows + j+1]);
                        addVertex(
                                    Vertex(
                                        QVector3D(nposX, posY, nposZ),
                                        QVector3D(color.r/255.0, color.g/255.0, color.b/255.0)
                                    )
                                );
                    }

                    if (k < rows -1 && j >0) {
                        color = getColor((unsigned char const *)&band_data[k*rows + j]);
                        glColor4d(color.r/255.0,color.g/255.0,color.b/255.0, color.a/255.0);
                        addVertex(
                                    Vertex(
                                        QVector3D(posX, posY, posZ),
                                        QVector3D(color.r/255.0, color.g/255.0, color.b/255.0)
                                    )
                                );

                        float nposY = (float)(centerY - (k +1))/centerY;
                        float nposZ = (float)band_data[(k+1)*rows + j] / maxZ;
                        color = getColor((unsigned char const *)&band_data[(k+1)*rows + j]);
                        addVertex(
                                    Vertex(
                                        QVector3D(posX, nposY, nposZ),
                                        QVector3D(color.r/255.0, color.g/255.0, color.b/255.0)
                                    )
                                );

                        float nposX = (float)(j -1 - centerX)/centerX;
                        nposZ = (float)band_data[(k)*rows + j -1] / maxZ;
                        color = getColor((unsigned char const *)&band_data[k*rows + j-1]);
                        addVertex(
                                    Vertex(
                                        QVector3D(nposX, posY, nposZ),
                                        QVector3D(color.r/255.0, color.g/255.0, color.b/255.0)
                                    )
                                );
                    }

                    if (k > 0 && j < cols -1) {
                        color = getColor((unsigned char const *)&band_data[k*rows + j]);
                        addVertex(
                                                            Vertex(
                                                                QVector3D(posX, posY, posZ),
                                                                QVector3D(color.r/255.0, color.g/255.0, color.b/255.0)
                                                            )
                                                        );

                        float nposY = (float)(centerY - (k -1))/centerY;
                        float nposZ = (float)band_data[(k-1)*rows + j] / maxZ;
                        color = getColor((unsigned char const *)&band_data[(k-1)*rows + j]);
                        addVertex(
                                                            Vertex(
                                                                QVector3D(posX, nposY, nposZ),
                                                                QVector3D(color.r/255.0, color.g/255.0, color.b/255.0)
                                                            )
                                                        );

                        float nposX = (float)(j +1 - centerX)/centerX;
                        nposZ = (float)band_data[(k)*rows + j +1] / maxZ;
                        color = getColor((unsigned char const *)&band_data[k*rows + j+1]);
                        addVertex(
                                                            Vertex(
                                                                QVector3D(nposX, posY, nposZ),
                                                                QVector3D(color.r/255.0, color.g/255.0, color.b/255.0)
                                                            )
                                                        );
                    }

                }
            }
//        glGenVertexArrays(1, &VertexArrayID);
//        glBindVertexArray(VertexArrayID);
        glGenBuffers(1, &vertexbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        qDebug() << "bind buffer. Err: "<< glGetError();
        glBufferData(GL_ARRAY_BUFFER, data_paint.size()*sizeof(float), data_paint.data(), GL_STATIC_DRAW);
        qDebug() << "bind Data. Error: " << glGetError();
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
//    glBegin(GL_TRIANGLES);
//    for(int i=0 ;i< data_vertex.size(); i++) {
//        Vertex v = data_vertex[i];
//        glVertex3f(v.position().x(), v.position().y(), v.position().z());
//        glColor3f(v.color().x(), v.color().y(), v.color().z());
//    }
//    glEnd();
    if (data_paint.size() > 0) {
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        qDebug() << "bind when paint. Err: "<< glGetError();
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);

//        glVertexPointer(3, GL_FLOAT, 6*sizeof(float), &data_paint[0]);
//        glColorPointer(3, GL_FLOAT, 6*sizeof(float), &data_paint[3]);
//        glDrawArrays(GL_TRIANGLES, 0, data_paint.size()/6);
        glVertexPointer(3, GL_FLOAT, 6*sizeof(float), 0);
        glColorPointer(3, GL_FLOAT, 6*sizeof(float), (GLvoid*)(3*sizeof(float)));
        glDrawArrays(GL_TRIANGLES, 0, data_paint.size()/6);

        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

    }

}
void FileGraphics::resizeGL(int width, int height)
{

}
