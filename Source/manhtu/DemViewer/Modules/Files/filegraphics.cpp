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
void FileGraphics::paintGL()
{
    if (fcontroller->getDemObject() != NULL)
    {
        int rows, cols;
        GDALDataset* pDataset = fcontroller->getDemObject()->getDataSet();
        cols = pDataset->GetRasterXSize();
        rows = pDataset->GetRasterYSize();
        setSize(cols, rows);

        int WWIDTH = cols;
        int WHEIGHT = rows;

        glClearColor( 0.0f, 0.0f, 0.0f, 0.0f);
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT  );

        glClearDepth(1.0f);

        glViewport(0, 0, WWIDTH, WHEIGHT);

        glMatrixMode(GL_PROJECTION);

        glLoadIdentity();

        glOrtho(0, WWIDTH, WHEIGHT, 0, 1, -1);

        glMatrixMode(GL_MODELVIEW);

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

            glBegin(GL_POINTS);

            for (int k = 0; k < rows; k++) {
                for (int j =0; j < cols; j++) {
                    unsigned char const * const p = (unsigned char const *)&band_data.data()[k*rows + j];
                    float r = p[0];
                    float g = p[1];
                    float b = p[2];
                    float a = p[3];

                    glColor4d(r/255.0,g/255.0,b/255.0, a/255.0);
                    glVertex2f(j,k);
                }
            }
            glEnd( );

        glFlush();
    }
}
void FileGraphics::resizeGL(int width, int height)
{

}
