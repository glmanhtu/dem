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

ColorRGBA FileGraphics::getColor(unsigned char const * const p) {
    ColorRGBA* c = new ColorRGBA();
    c->r = p[0];
    c->g = p[1];
    c->b = p[2];
    c->a = p[3];
    return *c;
}

void FileGraphics::paintGL()
{
    if (fcontroller->getDemObject() != NULL)
    {
        int rows, cols;
        GDALDataset* pDataset = fcontroller->getDemObject()->getGDALDataSet();
        cols = pDataset->GetRasterXSize();
        rows = pDataset->GetRasterYSize();
        setSize(cols, rows);

        int WWIDTH = cols;
        int WHEIGHT = rows;

        glClearColor( 0.0f, 0.0f, 0.0f, 0.0f);
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT  );

        glClearDepth(1.0f);

//        glViewport(0, 0, WWIDTH, WHEIGHT);

//        glMatrixMode(GL_PROJECTION);

//        glLoadIdentity();

//        glOrtho(0, WWIDTH, WHEIGHT, 0, 1, -1);

//        glMatrixMode(GL_MODELVIEW);

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
//            GLuint texture[1];
//            glEnable(GL_CULL_FACE);
//            glShadeModel(GL_SMOOTH);
//            glEnable(GL_BLEND);
//            glEnable(GL_TEXTURE_2D);

//            glGenTextures(1, &texture[0]);
//            glBindTexture(GL_TEXTURE_2D, texture[0]);

//            glTexImage2D(GL_TEXTURE_2D, 0, 4, cols, rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, band_data.data());
//            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
//            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
//            glBindTexture( GL_TEXTURE_2D, 0 );
//            glClearColor( 0.0f, 0.0f, 0.0f, 0.0f);
//            glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT  );
//            glMatrixMode( GL_PROJECTION );
//            glLoadIdentity();

//            glShadeModel( GL_FLAT );
//            glEnable(GL_LIGHTING);
//            glEnable(GL_LIGHT0);
//            glEnable(GL_DEPTH_TEST);
//            glEnable(GL_TEXTURE_2D);
//            glColor3f(0.5, 0.5, 0);
//            glBindTexture(GL_TEXTURE_2D, texture[0]);
//            glBegin(GL_QUADS);
//            glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0f, -1.0f);
//            glTexCoord2f(1.0f, 0.0f); glVertex2f(1.0f, -1.0f);
//            glTexCoord2f(1.0f, 1.0f); glVertex2f(1.0f, 1.0f);
//            glTexCoord2f(0.0f, 1.0f); glVertex2f(-1.0f, 1.0f);
//            glEnd();
//            glDisable(GL_TEXTURE_2D);
        //glRotatef(60.0f, 0.0f, 0.0f, 1.0f);

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
                        glColor4d(color.r/255.0,color.g/255.0,color.b/255.0, color.a/255.0);
                        glVertex3f(posX, posY, posZ);


                        float nposY = (float)(centerY - (k -1))/centerY;
                        float nposZ = (float)band_data[(k-1)*rows + j] / maxZ;
                        color = getColor((unsigned char const *)&band_data[(k-1)*rows + j]);
                        glColor4d(color.r/255.0,color.g/255.0,color.b/255.0, color.a/255.0);
                        glVertex3f(posX, nposY, nposZ);

                        float nposX = (float)(j -1 - centerX)/centerX;
                        nposZ = (float)band_data[k*rows + j -1] / maxZ;
                        color = getColor((unsigned char const *)&band_data[k*rows + j - 1]);
                        glColor4d(color.r/255.0,color.g/255.0,color.b/255.0, color.a/255.0);
                        glVertex3f(nposX, posY, nposZ);
                    }
                    if (k < rows -1 && j < cols -1) {
                        color = getColor((unsigned char const *)&band_data[k*rows + j]);
                        glColor4d(color.r/255.0,color.g/255.0,color.b/255.0, color.a/255.0);
                        glVertex3f(posX, posY, posZ);

                        float nposY = (float)(centerY - (k +1))/centerY;
                        float nposZ = (float)band_data[(k+1)*rows + j] / maxZ;
                        color = getColor((unsigned char const *)&band_data[(k+1)*rows + j]);
                        glColor4d(color.r/255.0,color.g/255.0,color.b/255.0, color.a/255.0);
                        glVertex3f(posX, nposY, nposZ);

                        float nposX = (float)(j +1 - centerX)/centerX;
                        nposZ = (float)band_data[(k)*rows + j +1] / maxZ;
                        color = getColor((unsigned char const *)&band_data[k*rows + j+1]);
                        glColor4d(color.r/255.0,color.g/255.0,color.b/255.0, color.a/255.0);
                        glVertex3f(nposX, posY, nposZ);
                    }

                    if (k < rows -1 && j >0) {
                        color = getColor((unsigned char const *)&band_data[k*rows + j]);
                        glColor4d(color.r/255.0,color.g/255.0,color.b/255.0, color.a/255.0);
                        glVertex3f(posX, posY, posZ);

                        float nposY = (float)(centerY - (k +1))/centerY;
                        float nposZ = (float)band_data[(k+1)*rows + j] / maxZ;
                        color = getColor((unsigned char const *)&band_data[(k+1)*rows + j]);
                        glColor4d(color.r/255.0,color.g/255.0,color.b/255.0, color.a/255.0);
                        glVertex3f(posX, nposY, nposZ);

                        float nposX = (float)(j -1 - centerX)/centerX;
                        nposZ = (float)band_data[(k)*rows + j -1] / maxZ;
                        color = getColor((unsigned char const *)&band_data[k*rows + j-1]);
                        glColor4d(color.r/255.0,color.g/255.0,color.b/255.0, color.a/255.0);
                        glVertex3f(nposX, posY, nposZ);
                    }

                    if (k > 0 && j < cols -1) {
                        color = getColor((unsigned char const *)&band_data[k*rows + j]);
                        glColor4d(color.r/255.0,color.g/255.0,color.b/255.0, color.a/255.0);
                        glVertex3f(posX, posY, posZ);

                        float nposY = (float)(centerY - (k -1))/centerY;
                        float nposZ = (float)band_data[(k-1)*rows + j] / maxZ;
                        color = getColor((unsigned char const *)&band_data[(k-1)*rows + j]);
                        glColor4d(color.r/255.0,color.g/255.0,color.b/255.0, color.a/255.0);
                        glVertex3f(posX, nposY, nposZ);

                        float nposX = (float)(j +1 - centerX)/centerX;
                        nposZ = (float)band_data[(k)*rows + j +1] / maxZ;
                        color = getColor((unsigned char const *)&band_data[k*rows + j+1]);
                        glColor4d(color.r/255.0,color.g/255.0,color.b/255.0, color.a/255.0);
                        glVertex3f(nposX, posY, nposZ);
                    }

                }
            }
            glEnd( );

        glFlush();
    }
}

void FileGraphics::resizeGL(int width, int height)
{

}
